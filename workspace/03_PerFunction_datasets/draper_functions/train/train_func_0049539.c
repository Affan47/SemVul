collPrevIterFCD(collIterate *data)
{
    const UChar *src, *start;
    uint8_t     leadingCC;
    uint8_t     trailingCC = 0;
    uint16_t    fcd;
    UBool       result = FALSE;

    start = data->string;
    src = data->pos + 1;


    fcd = g_nfcImpl->previousFCD16(start, src);

    leadingCC = (uint8_t)(fcd >> SECOND_LAST_BYTE_SHIFT_);

    if (leadingCC != 0) {


        for (;;)
        {
            if (start == src) {
                data->fcdPosition = NULL;
                return result;
            }

            fcd = g_nfcImpl->previousFCD16(start, src);

            trailingCC = (uint8_t)(fcd & LAST_BYTE_MASK_);

            if (trailingCC == 0) {
                break;
            }

            if (leadingCC < trailingCC) {
                result = TRUE;
            }

            leadingCC = (uint8_t)(fcd >> SECOND_LAST_BYTE_SHIFT_);
        }
    }

    data->fcdPosition = (UChar *)src;

    return result;
}
