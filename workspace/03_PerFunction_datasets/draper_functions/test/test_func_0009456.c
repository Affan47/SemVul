LUKS_open_key(const char *device,
		  unsigned int keyIndex,
		  const char *password,
		  size_t passwordLen,
		  struct luks_phdr *hdr,
		  struct luks_masterkey *mk,
		  struct crypt_device *ctx)
{
	crypt_keyslot_info ki = LUKS_keyslot_info(hdr, keyIndex);
	char derivedKey[hdr->keyBytes];
	char *AfKey;
	size_t AFEKSize;
	int r;

	log_dbg("Trying to open key slot %d [%d].", keyIndex, (int)ki);

	if (ki < CRYPT_SLOT_ACTIVE)
		return -ENOENT;


	AFEKSize = hdr->keyblock[keyIndex].stripes*mk->keyLength;
	AfKey = (char *)malloc(AFEKSize);
	if(AfKey == NULL) return -ENOMEM;

	r = PBKDF2_HMAC(hdr->hashSpec, password,passwordLen,
			hdr->keyblock[keyIndex].passwordSalt,LUKS_SALTSIZE,
			hdr->keyblock[keyIndex].passwordIterations,
			derivedKey, hdr->keyBytes);
	if(r < 0) goto out;

	log_dbg("Reading key slot %d area.", keyIndex);
	r = LUKS_decrypt_from_storage(AfKey,
				      AFEKSize,
				      hdr,
				      derivedKey,
				      hdr->keyBytes,
				      device,
				      hdr->keyblock[keyIndex].keyMaterialOffset,
				      ctx);
	if(r < 0) {
		log_err(ctx, _("Failed to read from key storage.\n"));
		goto out;
	}

	r = AF_merge(AfKey,mk->key,mk->keyLength,hdr->keyblock[keyIndex].stripes,hdr->hashSpec);
	if(r < 0) goto out;

	r = LUKS_verify_master_key(hdr, mk);
	if (r >= 0)
		log_verbose(ctx, _("Key slot %d unlocked.\n"), keyIndex);
out:
	free(AfKey);
	return r;
}
