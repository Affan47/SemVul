previousCC() {
    codePointLimit=codePointStart;
    if(reorderStart>=codePointStart) {
        return 0;
    }
    UChar32 c=*--codePointStart;
    if(c<Normalizer2Impl::MIN_CCC_LCCC_CP) {
        return 0;
    }

    UChar c2;
    if(U16_IS_TRAIL(c) && start<codePointStart && U16_IS_LEAD(c2=*(codePointStart-1))) {
        --codePointStart;
        c=U16_GET_SUPPLEMENTARY(c2, c);
    }
    return Normalizer2Impl::getCCFromYesOrMaybe(impl.getNorm16(c));
}
