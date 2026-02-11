pruneInvalidRecords()
{
    int idx = 0;
    IdxRecord idxRec ;
    StudyDescRecord *pStudyDesc;

    DB_lock(OFTrue);

    pStudyDesc = (StudyDescRecord *)malloc (SIZEOF_STUDYDESC) ;
    if (pStudyDesc == NULL) {
      DCMQRDB_WARN("DB_pruneInvalidRecords: out of memory");
      DB_unlock();
      return (DcmQRIndexDatabaseError) ;
    }

    for (int i = 0 ; i < handle_ -> maxStudiesAllowed ; i++ )
      pStudyDesc[i]. NumberofRegistratedImages = 0 ;

    DB_GetStudyDesc(pStudyDesc) ;

    while (DB_IdxRead(idx, &idxRec) == EC_Normal)
    {
      if (access(idxRec.filename, R_OK) < 0)
      {
#ifdef DEBUG
        DCMQRDB_DEBUG("*** Pruning Invalid DB Image Record: " << idxRec.filename);
#endif

        int studyIdx = matchStudyUIDInStudyDesc(pStudyDesc, idxRec.StudyInstanceUID, (int)(handle_->maxStudiesAllowed)) ;
        if (studyIdx < handle_->maxStudiesAllowed)
        {
          if (pStudyDesc[studyIdx].NumberofRegistratedImages > 0)
          {
            pStudyDesc[studyIdx].NumberofRegistratedImages--;
          } else {
            pStudyDesc[studyIdx].NumberofRegistratedImages = 0;
            pStudyDesc[studyIdx].StudySize = 0;
            pStudyDesc[studyIdx].StudyInstanceUID[0] = '\0';
          }
          if (pStudyDesc[studyIdx].StudySize > idxRec.ImageSize)
          {
            pStudyDesc[studyIdx].StudySize -= idxRec.ImageSize;
          }
        }


        DB_IdxRemove (idx);
      }
      idx++;
    }

    DB_StudyDescChange (pStudyDesc);
    DB_unlock();
    free (pStudyDesc) ;
    return EC_Normal;
}
