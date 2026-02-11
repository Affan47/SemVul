xmlSecSimpleKeysStoreFinalize(xmlSecKeyStorePtr store) {
    xmlSecPtrListPtr list;

    xmlSecAssert(xmlSecKeyStoreCheckId(store, xmlSecSimpleKeysStoreId));

    list = xmlSecSimpleKeysStoreGetList(store);
    xmlSecAssert(list != NULL);

    xmlSecPtrListFinalize(list);
}
