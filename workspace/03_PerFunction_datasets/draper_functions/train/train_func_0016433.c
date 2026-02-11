split(const UnicodeString &input,
        UnicodeString    dest[],
        int32_t          destCapacity,
        UErrorCode      &status)
{
    UText inputText = UTEXT_INITIALIZER;
    utext_openConstUnicodeString(&inputText, &input, &status);
    if (U_FAILURE(status)) {
        return 0;
    }

    UText **destText = (UText **)uprv_malloc(sizeof(UText*)*destCapacity);
    if (destText == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return 0;
    }
    int32_t i;
    for (i = 0; i < destCapacity; i++) {
        destText[i] = utext_openUnicodeString(NULL, &dest[i], &status);
    }

    int32_t fieldCount = split(&inputText, destText, destCapacity, status);

    for (i = 0; i < destCapacity; i++) {
        utext_close(destText[i]);
    }

    uprv_free(destText);
    utext_close(&inputText);
    return fieldCount;
}
