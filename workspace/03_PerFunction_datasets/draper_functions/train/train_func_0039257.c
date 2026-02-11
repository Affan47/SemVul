FileIsWritable(char *pcFileName)
{
    bool bFileAlreadyExisted;
    FILE *prFilePointer;
    bool bIsWritable;

    if (0 != CheckIfFileExists(pcFileName)) {
        bFileAlreadyExisted = TRUE;
    } else {
        bFileAlreadyExisted = FALSE;
    }

    if (NULL == (prFilePointer=fopen(pcFileName, "a"))) {
        bIsWritable = FALSE;
    } else {
        bIsWritable = TRUE;
        if (0 != fclose(prFilePointer)) {
            Log(&rLog, LOG_ERROR, "Couldn't close temporily created file %s. Expect trouble...");
        }
    }

#if 0
    LOG_DEBUG("%s existed?=%d writable=%d", pcFileName,
              (TRUE==bFileAlreadyExisted? 1 : 0),
              (TRUE==bIsWritable? 1:0));
#endif


    if (FALSE==bFileAlreadyExisted && TRUE==bIsWritable) {
        if (0 != remove(pcFileName)) {
            Log(&rLog, LOG_ERROR, "Removing of temporarily created file %s failed. Expect trouble...");
        }
    }
    return bIsWritable;
}
