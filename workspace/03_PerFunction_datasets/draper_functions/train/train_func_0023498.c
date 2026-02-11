parse_efi_signature_list(const void *data, size_t size, struct key *keyring)
{
	unsigned offs = 0;
	size_t lsize, esize, hsize, elsize;

	pr_devel("-->%s(,%zu)\n", __func__, size);

	while (size > 0) {
		efi_signature_list_t list;
		const efi_signature_data_t *elem;
		key_ref_t key;

		if (size < sizeof(list))
			return -EBADMSG;

		memcpy(&list, data, sizeof(list));
		pr_devel("LIST[%04x] guid=%pUl ls=%x hs=%x ss=%x\n",
			 offs,
			 list.signature_type.b, list.signature_list_size,
			 list.signature_header_size, list.signature_size);

		lsize = list.signature_list_size;
		hsize = list.signature_header_size;
		esize = list.signature_size;
		elsize = lsize - sizeof(list) - hsize;

		if (lsize > size) {
			pr_devel("<--%s() = -EBADMSG [overrun @%x]\n",
				 __func__, offs);
			return -EBADMSG;
		}
		if (lsize < sizeof(list) ||
		    lsize - sizeof(list) < hsize ||
		    esize < sizeof(*elem) ||
		    elsize < esize ||
		    elsize % esize != 0) {
			pr_devel("- bad size combo @%x\n", offs);
			return -EBADMSG;
		}

		if (efi_guidcmp(list.signature_type, efi_cert_x509_guid) != 0) {
			data += lsize;
			size -= lsize;
			offs += lsize;
			continue;
		}

		data += sizeof(list) + hsize;
		size -= sizeof(list) + hsize;
		offs += sizeof(list) + hsize;

		for (; elsize > 0; elsize -= esize) {
			elem = data;

			pr_devel("ELEM[%04x]\n", offs);

			key = key_create_or_update(
				make_key_ref(keyring, 1),
				"asymmetric",
				NULL,
				&elem->signature_data,
				esize - sizeof(*elem),
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW,
				KEY_ALLOC_NOT_IN_QUOTA |
				KEY_ALLOC_TRUSTED);

			if (IS_ERR(key))
				pr_err("Problem loading in-kernel X.509 certificate (%ld)\n",
				       PTR_ERR(key));
			else
				pr_notice("Loaded cert '%s' linked to '%s'\n",
					  key_ref_to_ptr(key)->description,
					  keyring->description);

			data += esize;
			size -= esize;
			offs += esize;
		}
	}

	return 0;
}
