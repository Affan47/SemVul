CMD_list_single(char *group)
{
    char *grplist[2] = { NULL, NULL };
    int lo, hi, count, flag;

    if (PERMspecified) {
        grplist[0] = group;
        if (!PERMmatch(PERMreadlist, grplist))
            return false;
    }
    if (OVgroupstats(group, &lo, &hi, &count, &flag) && flag != NF_FLAG_ALIAS) {

        if (PERMaccessconf->locpost && (flag == NF_FLAG_IGNORE
                                        || flag == NF_FLAG_JUNK
                                        || flag == NF_FLAG_NOLOCAL))
            flag = NF_FLAG_OK;


        if (count == 0)
            lo = hi + 1;
        Reply("%d %s\r\n", NNTP_OK_LIST, INFOactive.Format);
        Printf("%s %0*u %0*u %c\r\n", group, ARTNUMPRINTSIZE, hi,
               ARTNUMPRINTSIZE, lo, flag);
        Printf(".\r\n");
        return true;
    }
    return false;
}
