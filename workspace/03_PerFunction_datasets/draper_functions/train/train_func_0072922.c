unmap_object(x, y)
    register int x, y;
{
    register struct trap *trap;

    if (!level.flags.hero_memory) return;

    if ((trap = t_at(x,y)) != 0 && trap->tseen && !covers_traps(x,y))
	map_trap(trap, 0);
    else if (levl[x][y].seenv) {
	struct rm *lev = &levl[x][y];

	map_background(x, y, 0);


	if (!lev->waslit && lev->glyph == cmap_to_glyph(S_room) &&
							    lev->typ == ROOM)
	    lev->glyph = cmap_to_glyph(S_stone);
    } else
	levl[x][y].glyph = cmap_to_glyph(S_stone);
}
