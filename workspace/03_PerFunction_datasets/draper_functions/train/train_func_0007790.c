DB_StudyDescChange(StudyDescRecord *pStudyDesc)
{
    OFCondition cond = EC_Normal;
    DB_lseek (handle_ -> pidx, 0L, SEEK_SET) ;
    if (write (handle_ -> pidx, (char *) pStudyDesc, SIZEOF_STUDYDESC) != SIZEOF_STUDYDESC) cond = DcmQRIndexDatabaseError;
    DB_lseek (handle_ -> pidx, 0L, SEEK_SET) ;
    return cond ;
}
