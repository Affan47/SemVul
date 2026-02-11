hasFullCompositionExclusion(const BinaryProperty &, UChar32 c, UProperty ) {

    UErrorCode errorCode=U_ZERO_ERROR;
    const Normalizer2Impl *impl=Normalizer2Factory::getNFCImpl(errorCode);
    return U_SUCCESS(errorCode) && impl->isCompNo(impl->getNorm16(c));
}
