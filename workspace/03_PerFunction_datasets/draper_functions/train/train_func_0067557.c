DB_IdxRead (int idx, IdxRecord *idxRec)
{


    DB_lseek (handle_ -> pidx, (long) (SIZEOF_STUDYDESC + idx * SIZEOF_IDXRECORD), SEEK_SET) ;


    if (read (handle_ -> pidx, (char *) idxRec, SIZEOF_IDXRECORD) != SIZEOF_IDXRECORD)
        return (DcmQRIndexDatabaseError) ;

    DB_lseek (handle_ -> pidx, 0L, SEEK_SET) ;


    DB_IdxInitRecord (idxRec, 1) ;
    return EC_Normal ;
}
