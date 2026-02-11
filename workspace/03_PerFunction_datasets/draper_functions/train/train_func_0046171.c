R_DrawMasked (void)
{
    vissprite_t*	spr;
    drawseg_t*		ds;

    R_SortVisSprites ();

    if (vissprite_p > vissprites)
    {

	for (spr = vsprsortedhead.next ;
	     spr != &vsprsortedhead ;
	     spr=spr->next)
	{

	    R_DrawSprite (spr);
	}
    }


    for (ds=ds_p-1 ; ds >= drawsegs ; ds--)
	if (ds->maskedtexturecol)
	    R_RenderMaskedSegRange (ds, ds->x1, ds->x2);


    if (!viewangleoffset)
	R_DrawPlayerSprites ();
}
