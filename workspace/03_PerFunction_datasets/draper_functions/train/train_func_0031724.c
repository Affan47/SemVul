PyInit__hashlib(void)
{
    PyObject *m, *openssl_md_meth_names;

    OpenSSL_add_all_digests();


    Py_TYPE(&EVPtype) = &PyType_Type;
    if (PyType_Ready(&EVPtype) < 0)
        return NULL;

    m = PyModule_Create(&_hashlibmodule);
    if (m == NULL)
        return NULL;

    openssl_md_meth_names = generate_hash_name_list();
    if (openssl_md_meth_names == NULL) {
        Py_DECREF(m);
        return NULL;
    }
    if (PyModule_AddObject(m, "openssl_md_meth_names", openssl_md_meth_names)) {
        Py_DECREF(m);
        return NULL;
    }

#if HASH_OBJ_CONSTRUCTOR
    Py_INCREF(&EVPtype);
    PyModule_AddObject(m, "HASH", (PyObject *)&EVPtype);
#endif


    INIT_CONSTRUCTOR_CONSTANTS(md5);
    INIT_CONSTRUCTOR_CONSTANTS(sha1);
#ifdef _OPENSSL_SUPPORTS_SHA2
    INIT_CONSTRUCTOR_CONSTANTS(sha224);
    INIT_CONSTRUCTOR_CONSTANTS(sha256);
    INIT_CONSTRUCTOR_CONSTANTS(sha384);
    INIT_CONSTRUCTOR_CONSTANTS(sha512);
#endif
    return m;
}
