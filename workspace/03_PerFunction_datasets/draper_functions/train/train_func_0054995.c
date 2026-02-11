unorm_iterate(UCharIterator *src, UBool forward,
              UChar *dest, int32_t destCapacity,
              UNormalizationMode mode, int32_t options,
              UBool doNormalize, UBool *pNeededToNormalize,
              UErrorCode *pErrorCode) {
    const Normalizer2 *n2=Normalizer2Factory::getInstance(mode, *pErrorCode);
    if(options&UNORM_UNICODE_3_2) {
        const UnicodeSet *uni32 = uniset_getUnicode32Instance(*pErrorCode);
        if(U_FAILURE(*pErrorCode)) {
            return 0;
        }
        FilteredNormalizer2 fn2(*n2, *uni32);
        return _iterate(src, forward, dest, destCapacity,
            &fn2, doNormalize, pNeededToNormalize, pErrorCode);
    }
    return _iterate(src, forward, dest, destCapacity,
            n2, doNormalize, pNeededToNormalize, pErrorCode);
}
