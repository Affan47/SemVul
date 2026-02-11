CurrentLayer (DBInt layerID)
		{
		if (layerID == DBFault) LayerRec = GridIF->Layer (0);
		else	LayerRec = layerID < GridIF->LayerNum () ? GridIF->Layer (layerID) :
								GridIF->Layer (layerID % GridIF->LayerNum ());
		return (LayerRec->Name ());
		}
