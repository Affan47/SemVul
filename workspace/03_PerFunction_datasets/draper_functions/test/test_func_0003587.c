handleCE32(UChar32 start, UChar32 end, uint32_t ce32) {
    U_ASSERT(ce32 != Collation::FALLBACK_CE32);
    if(Collation::isSpecialCE32(ce32)) {
        ce32 = data->getIndirectCE32(ce32);
        if(ce32 == Collation::FALLBACK_CE32) {
            return U_SUCCESS(errorCode);
        }
    }
    do {
        uint32_t baseCE32 = baseData->getFinalCE32(baseData->getCE32(start));


        if(Collation::isSelfContainedCE32(ce32) && Collation::isSelfContainedCE32(baseCE32)) {

            if(ce32 != baseCE32) {
                tailored->add(start);
            }
        } else {
            compare(start, ce32, baseCE32);
        }
    } while(++start <= end);
    return U_SUCCESS(errorCode);
}
