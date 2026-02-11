NC_reader(CHANNEL *cp)
{
    char buff[SMBUF];

    cp->Start = cp->Next;

    if (!cp->CanAuthenticate || innconf->noreader
     || (NNRPReason != NULL && !innconf->readerswhenstopped))
        snprintf(buff, sizeof(buff), "%d Permission denied",
                 NNTP_ERR_ACCESS);
    else
        snprintf(buff, sizeof(buff), "%d MODE-READER",
                 NNTP_FAIL_WRONG_MODE);
    NCwritereply(cp, buff);
}
