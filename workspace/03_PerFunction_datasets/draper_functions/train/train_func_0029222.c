deleteCellFunc (Tile * tile, UserData data)
{

	struct searchArg * arg = (struct searchArg *) data;


    if ( RIGHT(tile) == arg->rect->xmaxi)
    {
        if (YMIN(tile) == arg->rect->ymini)
            cellTileMerge (tile, arg->plane, TOPBOTTOMLEFTRIGHT);
        else
            cellTileMerge (tile, arg->plane, TOPLEFTRIGHT);
    }
    else if (YMIN(tile) == arg->rect->ymini)
            cellTileMerge (tile, arg->plane, TOPBOTTOMLEFT);
    else
    	    cellTileMerge (tile, arg->plane, TOPLEFT);
    return (0);
}
