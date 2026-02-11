convertString(T_Descriptor descriptor,
                                               const char *fromString,
                                               const size_t fromLength,
                                               OFString &toString,
                                               const OFBool clearMode)
{

    if (clearMode)
        toString.clear();
#ifdef WITH_LIBICONV
    OFCondition status = EC_Normal;

    if (isDescriptorValid(descriptor))
    {
#if _LIBICONV_VERSION >= 0x0108

        int translit = (TransliterationMode) ? 1 : 0;
        if (::iconvctl(descriptor, ICONV_SET_TRANSLITERATE, &translit) < 0)
        {

            createErrnoCondition(status, "Cannot control character encoding feature TRANSLITERATE: ",
                EC_CODE_CannotControlConverter);
        }

        int discard = (DiscardIllegalSequenceMode) ? 1 : 0;
        if (::iconvctl(descriptor, ICONV_SET_DISCARD_ILSEQ, &discard) < 0)
        {

            createErrnoCondition(status, "Cannot control character encoding feature DISCARD_ILSEQ: ",
                EC_CODE_CannotControlConverter);
        }
#endif

        if (status.good() && (fromString != NULL) && (fromLength > 0))
        {
#ifdef LIBICONV_SECOND_ARGUMENT_CONST
            const char *inputPos = fromString;
#else
            char *inputPos = OFconst_cast(char *, fromString);
#endif
            size_t inputLeft = fromLength;

            ::iconv(descriptor, NULL, NULL, NULL, NULL);

            while (inputLeft > 0)
            {
                char buffer[CONVERSION_BUFFER_SIZE];
                char *bufferPos = buffer;
                const size_t bufferLength = sizeof(buffer);
                size_t bufferLeft = bufferLength;

                if (::iconv(descriptor, &inputPos, &inputLeft, &bufferPos, &bufferLeft) == CONVERSION_ERROR)
                {


                    if ((errno != E2BIG) || (bufferLeft == bufferLength))
                    {

                        createErrnoCondition(status, "Cannot convert character encoding: ",
                            EC_CODE_CannotConvertEncoding);
                        break;
                    }
                }

                toString.append(buffer, bufferLength - bufferLeft);
            }
        }
    } else
        status = EC_NoEncodingSelected;
    return status;
#else
    return EC_NoEncodingLibrary;
#endif
}
