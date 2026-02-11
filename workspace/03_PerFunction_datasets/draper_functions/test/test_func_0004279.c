getSamplesFromString(const UnicodeString &samples, double *dest,
                        int32_t destCapacity, UErrorCode& status) {
    int32_t sampleCount = 0;
    int32_t sampleStartIdx = 0;
    int32_t sampleEndIdx = 0;


    for (sampleCount = 0; sampleCount < destCapacity && sampleStartIdx < samples.length(); ) {
        sampleEndIdx = samples.indexOf(COMMA, sampleStartIdx);
        if (sampleEndIdx == -1) {
            sampleEndIdx = samples.length();
        }
        const UnicodeString &sampleRange = samples.tempSubStringBetween(sampleStartIdx, sampleEndIdx);


        int32_t tildeIndex = sampleRange.indexOf(TILDE);
        if (tildeIndex < 0) {
            FixedDecimal fixed(sampleRange, status);
            double sampleValue = fixed.source;
            if (fixed.visibleDecimalDigitCount == 0 || sampleValue != floor(sampleValue)) {
                dest[sampleCount++] = sampleValue;
            }
        } else {

            FixedDecimal fixedLo(sampleRange.tempSubStringBetween(0, tildeIndex), status);
            FixedDecimal fixedHi(sampleRange.tempSubStringBetween(tildeIndex+1), status);
            double rangeLo = fixedLo.source;
            double rangeHi = fixedHi.source;
            if (U_FAILURE(status)) {
                break;
            }
            if (rangeHi < rangeLo) {
                status = U_INVALID_FORMAT_ERROR;
                break;
            }


            double scale = scaleForInt(rangeLo);
            double t = scaleForInt(rangeHi);
            if (t > scale) {
                scale = t;
            }
            rangeLo *= scale;
            rangeHi *= scale;
            for (double n=rangeLo; n<=rangeHi; n+=1) {


                double sampleValue = n/scale;
                if (!(sampleValue == floor(sampleValue) && fixedLo.visibleDecimalDigitCount > 0)) {
                    dest[sampleCount++] = sampleValue;
                }
                if (sampleCount >= destCapacity) {
                    break;
                }
            }
        }
        sampleStartIdx = sampleEndIdx + 1;
    }
    return sampleCount;
}
