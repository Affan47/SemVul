nextInput(ByteInStream & is, StdVnChar & stdChar, int & bytesRead)
{
    if (!is.getNextDW(stdChar)) {
        bytesRead = 0;
        return 0;
    }
    bytesRead = sizeof(UKDWORD);
    return 1;
}
