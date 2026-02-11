R_NewVisSprite (void)
{
    if (vissprite_p == &vissprites[MAXVISSPRITES])
	return &overflowsprite;

    vissprite_p++;
    return vissprite_p-1;
}
