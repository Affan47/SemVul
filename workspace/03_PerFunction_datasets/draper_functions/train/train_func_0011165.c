flashErasePages(u32 pageAddr, u16 n) {
    while (n-- > 0) {
        if (!flashErasePage(pageAddr + 0x400 * n)) {
            return FALSE;
        }
    }

    return TRUE;
}
