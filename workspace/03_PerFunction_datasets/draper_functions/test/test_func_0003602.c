PK11_PubUnwrapSymKey(SECKEYPrivateKey *wrappingKey, SECItem *wrappedKey,
	  CK_MECHANISM_TYPE target, CK_ATTRIBUTE_TYPE operation, int keySize)
{
    CK_MECHANISM_TYPE wrapType = pk11_mapWrapKeyType(wrappingKey->keyType);
    PK11SlotInfo    *slot = wrappingKey->pkcs11Slot;

    if (SECKEY_HAS_ATTRIBUTE_SET(wrappingKey,CKA_PRIVATE)) {
	PK11_HandlePasswordCheck(slot,wrappingKey->wincx);
    }

    return pk11_AnyUnwrapKey(slot, wrappingKey->pkcs11ID,
	wrapType, NULL, wrappedKey, target, operation, keySize,
	wrappingKey->wincx, NULL, 0, PR_FALSE);
}
