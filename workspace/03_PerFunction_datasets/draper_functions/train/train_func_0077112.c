WI_drawOnLnode
( int		n,
  patch_t*	c[] )
{

    int		i;
    int		left;
    int		top;
    int		right;
    int		bottom;
    boolean	fits = false;

    i = 0;
    do
    {
	left = lnodes[wbs->epsd][n].x - SHORT(c[i]->leftoffset);
	top = lnodes[wbs->epsd][n].y - SHORT(c[i]->topoffset);
	right = left + SHORT(c[i]->width);
	bottom = top + SHORT(c[i]->height);

	if (left >= 0
	    && right < SCREENWIDTH
	    && top >= 0
	    && bottom < SCREENHEIGHT)
	{
	    fits = true;
	}
	else
	{
	    i++;
	}
    } while (!fits && i!=2 && c[i] != NULL);

    if (fits && i<2)
    {
	V_DrawPatch(lnodes[wbs->epsd][n].x,
                    lnodes[wbs->epsd][n].y,
		    c[i]);
    }
    else
    {

	printf("Could not place patch on level %d", n+1);
    }
}
