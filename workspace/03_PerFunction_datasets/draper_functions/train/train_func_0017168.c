LoadGeometryLineStringHP()
{
    int          nInvalid, nGeometries;
    int          rowId;
    long         iFID;

    CPLString    osColumn, osSQL;
    const char  *vrColumn[2];
    GUIntBig     vrValue[2];

    sqlite3_stmt *hStmt;

    OGRGeometry        *poOgrGeometry;
    VFKReaderSQLite    *poReader;
    VFKDataBlockSQLite *poDataBlockLines;
    VFKFeatureSQLite   *poFeature, *poLine;

    nInvalid = nGeometries = 0;
    poReader  = (VFKReaderSQLite*) m_poReader;

    poDataBlockLines = (VFKDataBlockSQLite *) m_poReader->GetDataBlock("SBP");
    if (NULL == poDataBlockLines) {
        CPLError(CE_Failure, CPLE_FileIO,
                 "Data block %s not found", m_pszName);
        return nInvalid;
    }

    poDataBlockLines->LoadGeometry();

    if (LoadGeometryFromDB())
	return 0;

    osColumn.Printf("%s_ID", m_pszName);
    vrColumn[0] = osColumn.c_str();
    vrColumn[1] = "PORADOVE_CISLO_BODU";
    vrValue[1]  = 1;

    osSQL.Printf("SELECT ID,%s,rowid FROM %s", FID_COLUMN, m_pszName);

    if (EQUAL(m_pszName, "DPM"))
        osSQL += " WHERE SOURADNICE_X IS NULL";
    hStmt = poReader->PrepareStatement(osSQL.c_str());

    if (poReader->IsSpatial())
	poReader->ExecuteSQL("BEGIN");

    while(poReader->ExecuteSQL(hStmt) == OGRERR_NONE) {

        vrValue[0] = sqlite3_column_double(hStmt, 0);
        iFID       = sqlite3_column_double(hStmt, 1);
        rowId      = sqlite3_column_int(hStmt, 2);

        poFeature = (VFKFeatureSQLite *) GetFeatureByIndex(rowId - 1);
        CPLAssert(NULL != poFeature && poFeature->GetFID() == iFID);

        poLine = poDataBlockLines->GetFeature(vrColumn, vrValue, 2, TRUE);
	if (!poLine) {
	    poOgrGeometry = NULL;
	}
	else {
	    poOgrGeometry = poLine->GetGeometry();
	}
	if (!poOgrGeometry || !poFeature->SetGeometry(poOgrGeometry)) {
	    nInvalid++;
            continue;
        }


	if (poReader->IsSpatial() &&
	    SaveGeometryToDB(poOgrGeometry, rowId) != OGRERR_FAILURE &&
	    poOgrGeometry)
	    nGeometries++;
    }


    UpdateVfkBlocks(nGeometries);

    if (poReader->IsSpatial())
	poReader->ExecuteSQL("COMMIT");

    return nInvalid;
}
