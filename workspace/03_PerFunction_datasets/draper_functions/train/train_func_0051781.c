getLong()
{
    int32_t result = 0;
    if (fDecNumber->digits + fDecNumber->exponent > 10) {

        return result;
    }
    if (fDecNumber->exponent != 0) {


        DigitList copy(*this);
        DigitList zero;
        uprv_decNumberQuantize(copy.fDecNumber, copy.fDecNumber, zero.fDecNumber, &fContext);
        result = uprv_decNumberToInt32(copy.fDecNumber, &fContext);
    } else {
        result = uprv_decNumberToInt32(fDecNumber, &fContext);
    }
    return result;
}
