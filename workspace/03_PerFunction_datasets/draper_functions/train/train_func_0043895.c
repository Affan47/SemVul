Node (DBCoordinate coord,DBInt create)

	{
	DBFloat precision = pow ((double) 10.0,(double) Data ()->Precision ());
	DBObjRecord *nodeRec;

	for (nodeRec = NodeTable->First ();nodeRec != (DBObjRecord *) NULL;nodeRec = NodeTable->Next ())
		if (DBMathCartesianDistance (coord,NodeCoordFLD->Coordinate (nodeRec)) < precision) return (nodeRec);
	if (create)
		{
		char objName [DBStringLength];

		sprintf (objName,"Node: %5d",NodeTable->ItemNum ());
		nodeRec = NodeTable->Add (objName);
		NodeCoordFLD->Coordinate (nodeRec,coord);
		return (nodeRec);
		}
	return ((DBObjRecord *) NULL);
	}
