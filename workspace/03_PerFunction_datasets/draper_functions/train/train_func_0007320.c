IO_FlushBuffer(reader* globalData) {

    HANDLE handle = globalData->io.handle;

    if (tcflush(handle, TCIFLUSH) == 0)
        return TRUE;
    return FALSE;

}
