DeleteLayers (char *firstLayer, char *lastLayer)

	{
	DBInt layerID;
	DBObjRecord *layerRec;

	if ((layerRec = LayerTable->Item (firstLayer)) == (DBObjRecord *) NULL)
		{ CMmsgPrint (CMmsgAppError, "Invalid layer name in: %s %d",__FILE__,__LINE__); return (DBFault); }
	layerID = layerRec->RowID ();

	while (strcmp (layerRec->Name (),lastLayer) != 0)
		{
		DeleteLayer (layerRec->Name());
		if ((layerRec = LayerTable->Item (layerID)) == (DBObjRecord *) NULL) break;
		}

	return (DBSuccess);
	}
