RGlibMinMax (DBObjData *tsData,DBObjData *data,bool doMin)

	{
	DBInt tsLayerID, layerID;
	DBFloat value, searchVal;
	DBPosition pos;
	DBObjRecord *layerRec;
	DBGridIF *tsGridIF = new DBGridIF (tsData);
	DBGridIF *gridIF   = new DBGridIF (data);

	if ((tsGridIF->RowNum () != gridIF->RowNum ()) || (tsGridIF->ColNum () != gridIF->ColNum ()))
		{ delete tsGridIF; delete gridIF; return (DBFault); }

	for (pos.Row = 0;pos.Row < tsGridIF->RowNum ();pos.Row++)
		for (pos.Col = 0;pos.Col < tsGridIF->ColNum ();pos.Col++)
			{
			searchVal = doMin ? HUGE_VAL : - HUGE_VAL;
			layerID = DBFault;
			for (tsLayerID = 0;tsLayerID < tsGridIF->LayerNum ();++tsLayerID)
				{
				layerRec = tsGridIF->Layer (tsLayerID);
				if (tsGridIF->Value (layerRec,pos,&value))
					{
					if (doMin)
						{
						if (value < searchVal)
							{
							searchVal = value;
							layerID   = tsLayerID;
							}
						}
					else
						{
						if (value > searchVal)
							{
							searchVal = value;
							layerID   = tsLayerID;
							}
						}
					}
				}
			if (layerID != DBFault)
					gridIF->Value (pos,layerID);
			else	gridIF->Value (pos,gridIF->MissingValue ());
			}
	gridIF->RenameLayer ((char *) "XXXX");
	gridIF->RecalcStats ();

	delete tsGridIF;
	delete gridIF;
	return (DBSuccess);
	}
