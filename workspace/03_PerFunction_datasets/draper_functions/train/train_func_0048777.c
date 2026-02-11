DownStreamSearch (DBObjRecord *cellRec,DBNetworkACTION forAction,DBNetworkACTION backAction,void *data)

	{
	DBObjRecord *toCell;

	if ((forAction != (DBNetworkACTION) NULL) && ((*forAction) (this,cellRec,data) == true))
		if ((toCell = ToCell (cellRec)) != (DBObjRecord *) NULL)
			DownStreamSearch (toCell,forAction,backAction,data);
	if (backAction != (DBNetworkACTION) NULL) (*backAction) (this,cellRec,data);
	}
