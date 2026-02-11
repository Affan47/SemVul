SendCAPy (unsigned int iAbsY)
{
    if (iAbsY == 0)
    {
        return thePrinter->Send ((const BYTE *) "\033*p0Y", 5);
    }
    return NO_ERROR;
}
