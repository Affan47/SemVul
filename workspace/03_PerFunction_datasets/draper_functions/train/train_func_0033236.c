P_LoadThings (int lump)
{
    byte               *data;
    int			i;
    mapthing_t         *mt;
    mapthing_t          spawnthing;
    int			numthings;
    boolean		spawn;

    data = W_CacheLumpNum (lump,PU_STATIC);
    numthings = W_LumpLength (lump) / sizeof(mapthing_t);

    mt = (mapthing_t *)data;
    for (i=0 ; i<numthings ; i++, mt++)
    {
	spawn = true;


	if (gamemode != commercial)
	{
	    switch (SHORT(mt->type))
	    {
	      case 68:
	      case 64:
	      case 88:
	      case 89:
	      case 69:
	      case 67:
	      case 71:
	      case 65:
	      case 66:
	      case 84:
		spawn = false;
		break;
	    }
	}
	if (spawn == false)
	    break;


	spawnthing.x = SHORT(mt->x);
	spawnthing.y = SHORT(mt->y);
	spawnthing.angle = SHORT(mt->angle);
	spawnthing.type = SHORT(mt->type);
	spawnthing.options = SHORT(mt->options);

	P_SpawnMapThing(&spawnthing);
    }

    W_ReleaseLumpNum(lump);
}
