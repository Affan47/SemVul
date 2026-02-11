RtlMultiByteToUnicodeN(
   IN PWCHAR UnicodeString,
   IN ULONG UnicodeSize,
   IN PULONG ResultSize,
   IN PCSTR MbString,
   IN ULONG MbSize)
{
    ULONG Size = 0;
    ULONG i;
    PUCHAR WideString;


    if (MbSize > (UnicodeSize / sizeof(WCHAR)))
        Size = UnicodeSize / sizeof(WCHAR);
    else
        Size = MbSize;

    if (ResultSize != NULL)
        *ResultSize = Size * sizeof(WCHAR);

    WideString = (PUCHAR)UnicodeString;
    for (i = 0; i < Size; i++)
    {
        WideString[2 * i + 0] = (UCHAR)MbString[i];
        WideString[2 * i + 1] = 0;
    }

    return STATUS_SUCCESS;
}
