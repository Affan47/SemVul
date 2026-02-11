mmc_prevent_allow_medium_removal(const CdIo_t *p_cdio,
				 bool b_persistent, bool b_prevent,
				 unsigned int i_timeout_ms)
{
    uint8_t buf[8] = { 0, };
    void   *p_buf  = &buf;
    const unsigned int i_size = 0;

    MMC_CMD_SETUP(CDIO_MMC_GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL);
    if (0 == i_timeout_ms) i_timeout_ms = mmc_timeout_ms;
    if (b_prevent)         cdb.field[4] |= 1;
    if (b_persistent)      cdb.field[4] |= 2;

    return MMC_RUN_CMD(SCSI_MMC_DATA_WRITE, i_timeout_ms);
}
