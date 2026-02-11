Delta (const DBObjRecord *cellRec) const
	{
	DBInt toCell = ToCellFLD->Int (cellRec);
	DBCoordinate delta (0.0, 0.0);

	if ((toCell == DBNetDirNW) || (toCell == DBNetDirN) || (toCell == DBNetDirNE)) delta.Y =   CellHeight ();
	if ((toCell == DBNetDirSE) || (toCell == DBNetDirS) || (toCell == DBNetDirSW)) delta.Y = - CellHeight ();
	if ((toCell == DBNetDirNE) || (toCell == DBNetDirE) || (toCell == DBNetDirSE)) delta.X =   CellWidth ();
	if ((toCell == DBNetDirNW) || (toCell == DBNetDirW) || (toCell == DBNetDirSW)) delta.X = - CellWidth ();
	return (delta);
	}
