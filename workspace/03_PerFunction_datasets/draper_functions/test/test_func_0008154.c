ftpSendMdtm(FtpStateData * ftpState)
{
    assert(*ftpState->filepath != '\0');
    snprintf(cbuf, 1024, "MDTM %s\r\n", ftpState->filepath);
    ftpWriteCommand(cbuf, ftpState);
    ftpState->state = SENT_MDTM;
}
