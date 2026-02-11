getInclusions(int32_t src, UErrorCode &status) {
    UBool needInit;
    UMTX_CHECK(NULL, (INCLUSIONS[src] == NULL), needInit);
    if (needInit) {
        UnicodeSet* incl = new UnicodeSet();
        USetAdder sa = {
            (USet *)incl,
            _set_add,
            _set_addRange,
            _set_addString,
            NULL,
            NULL
        };
        incl->ensureCapacity(DEFAULT_INCLUSION_CAPACITY, status);
        if (incl != NULL) {
            switch(src) {
            case UPROPS_SRC_CHAR:
                uchar_addPropertyStarts(&sa, &status);
                break;
            case UPROPS_SRC_PROPSVEC:
                upropsvec_addPropertyStarts(&sa, &status);
                break;
            case UPROPS_SRC_CHAR_AND_PROPSVEC:
                uchar_addPropertyStarts(&sa, &status);
                upropsvec_addPropertyStarts(&sa, &status);
                break;
#if !UCONFIG_NO_NORMALIZATION
            case UPROPS_SRC_CASE_AND_NORM: {
                const Normalizer2Impl *impl=Normalizer2Factory::getNFCImpl(status);
                if(U_SUCCESS(status)) {
                    impl->addPropertyStarts(&sa, status);
                }
                ucase_addPropertyStarts(ucase_getSingleton(), &sa, &status);
                break;
            }
            case UPROPS_SRC_NFC: {
                const Normalizer2Impl *impl=Normalizer2Factory::getNFCImpl(status);
                if(U_SUCCESS(status)) {
                    impl->addPropertyStarts(&sa, status);
                }
                break;
            }
            case UPROPS_SRC_NFKC: {
                const Normalizer2Impl *impl=Normalizer2Factory::getNFKCImpl(status);
                if(U_SUCCESS(status)) {
                    impl->addPropertyStarts(&sa, status);
                }
                break;
            }
            case UPROPS_SRC_NFKC_CF: {
                const Normalizer2Impl *impl=Normalizer2Factory::getNFKC_CFImpl(status);
                if(U_SUCCESS(status)) {
                    impl->addPropertyStarts(&sa, status);
                }
                break;
            }
            case UPROPS_SRC_NFC_CANON_ITER: {
                const Normalizer2Impl *impl=Normalizer2Factory::getNFCImpl(status);
                if(U_SUCCESS(status)) {
                    impl->addCanonIterPropertyStarts(&sa, status);
                }
                break;
            }
#endif
            case UPROPS_SRC_CASE:
                ucase_addPropertyStarts(ucase_getSingleton(), &sa, &status);
                break;
            case UPROPS_SRC_BIDI:
                ubidi_addPropertyStarts(ubidi_getSingleton(), &sa, &status);
                break;
            default:
                status = U_INTERNAL_PROGRAM_ERROR;
                break;
            }
            if (U_SUCCESS(status)) {

                incl->compact();
                umtx_lock(NULL);
                if (INCLUSIONS[src] == NULL) {
                    INCLUSIONS[src] = incl;
                    incl = NULL;
                    ucln_common_registerCleanup(UCLN_COMMON_USET, uset_cleanup);
                }
                umtx_unlock(NULL);
            }
            delete incl;
        } else {
            status = U_MEMORY_ALLOCATION_ERROR;
        }
    }
    return INCLUSIONS[src];
}
