isIdentical(UnicodeString &pattern, int32_t start, int32_t end)
{
    if (strength < UCOL_IDENTICAL) {
        return TRUE;
    }


    UErrorCode status = U_ZERO_ERROR;
    UnicodeString t2, p2;
    nfd.normalize(UnicodeString(FALSE, targetBuffer + start, end - start), t2, status);
    nfd.normalize(pattern, p2, status);

    return U_SUCCESS(status) && t2 == p2;
}
