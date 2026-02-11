SendPrinterReadyData
(
    BYTE* stream,
    unsigned int size
)
{
    if (stream == NULL)
    {
        return NULL_POINTER;
    }

    if (thePrinter == NULL)
    {
        return NO_PRINTER_SELECTED;
    }

    return thePrinter->Send(stream, size);
}
