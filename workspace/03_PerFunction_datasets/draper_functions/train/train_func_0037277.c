registerIDs() {

    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-NFC"),
                                     _create, cstrToken("nfc\0\0"));
    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-NFKC"),
                                     _create, cstrToken("nfkc\0\0"));
    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-NFD"),
                                     _create, cstrToken("nfc\0\1"));
    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-NFKD"),
                                     _create, cstrToken("nfkc\0\1"));
    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-FCD"),
                                     _create, cstrToken("nfc\0\2"));
    Transliterator::_registerFactory(UNICODE_STRING_SIMPLE("Any-FCC"),
                                     _create, cstrToken("nfc\0\3"));
    Transliterator::_registerSpecialInverse(UNICODE_STRING_SIMPLE("NFC"),
                                            UNICODE_STRING_SIMPLE("NFD"), TRUE);
    Transliterator::_registerSpecialInverse(UNICODE_STRING_SIMPLE("NFKC"),
                                            UNICODE_STRING_SIMPLE("NFKD"), TRUE);
    Transliterator::_registerSpecialInverse(UNICODE_STRING_SIMPLE("FCC"),
                                            UNICODE_STRING_SIMPLE("NFD"), FALSE);
    Transliterator::_registerSpecialInverse(UNICODE_STRING_SIMPLE("FCD"),
                                            UNICODE_STRING_SIMPLE("FCD"), FALSE);
}
