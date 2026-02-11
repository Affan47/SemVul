TI_actualizeStudies()
{
    TI_DBEntry *db;

    db = dbEntries[currentdb];


    if (!TI_buildStudies(db))
        return OFFalse;

    if (db->studyCount == 0) {
        printf("No Studies in Database: %s\n", db->title);
        return OFFalse;
    }

    if (db->currentStudy < 0 || db->currentStudy >= db->studyCount)
        db->currentStudy = 0;

    return OFTrue;
}
