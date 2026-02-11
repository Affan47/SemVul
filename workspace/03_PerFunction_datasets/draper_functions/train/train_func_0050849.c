init() {
    UErrorCode errorCode=U_ZERO_ERROR;
    fNorm2=Normalizer2Factory::getInstance(fUMode, errorCode);
    if(fOptions&UNORM_UNICODE_3_2) {
        delete fFilteredNorm2;
        fNorm2=fFilteredNorm2=
            new FilteredNormalizer2(*fNorm2, *uniset_getUnicode32Instance(errorCode));
    }
    if(U_FAILURE(errorCode)) {
        errorCode=U_ZERO_ERROR;
        fNorm2=Normalizer2Factory::getNoopInstance(errorCode);
    }
}
