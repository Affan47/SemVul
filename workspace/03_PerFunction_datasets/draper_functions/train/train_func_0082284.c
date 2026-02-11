LayerIsDated (DBInt layerID)
		{
		DBObjRecord *layerRec;
		DBDate date;
		layerRec = GridIF->Layer (layerID);
		date.Set (layerRec->Name ());
		if (date.Year () != DBDefaultMissingIntVal) return (true);
		return (date.Month () != DBDefaultMissingIntVal ? true : false);
		}
