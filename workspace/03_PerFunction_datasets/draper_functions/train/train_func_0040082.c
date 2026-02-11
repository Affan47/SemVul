DMCSetWhiteBalance(int fd, int mode)
{
    uint8_t userInterfaceSettings[16];
    SANE_Status status;
    size_t len;

    DBG(3, "DMCSetWhiteBalance: %d\n", mode);
    status = DMCRead(fd, 0x82, 0x0, userInterfaceSettings,
		     sizeof(userInterfaceSettings), &len);
    if (status != SANE_STATUS_GOOD) return status;
    if (len < sizeof(userInterfaceSettings)) return SANE_STATUS_IO_ERROR;

    userInterfaceSettings[5] = (uint8_t) mode;

    return DMCWrite(fd, 0x82, 0x0, userInterfaceSettings,
		    sizeof(userInterfaceSettings));
}
