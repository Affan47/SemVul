longdeadend_p(struct state *st, int x1, int y1, int x2, int y2, int endwall)
{
    int dx = x2 - x1, dy = y2 - y1;
    int sidewalls;

    sidewalls = endwall | (endwall >> 2 | endwall << 2);
    sidewalls = ~sidewalls & WALL_ANY;

    while((st->maze[x2][y2] & WALL_ANY) == sidewalls)
    {
        if (x2 + dx < 0 || x2 + dx >= st->maze_size_x ||
            y2 + dy < 0 || y2 + dy >= st->maze_size_y)
          break;
	x2 += dx;
	y2 += dy;
    }

    if((st->maze[x2][y2] & WALL_ANY) == (sidewalls | endwall))
    {
	endwall = (endwall >> 2 | endwall << 2) & WALL_ANY;
	while(x1 != x2 || y1 != y2)
	{
	    x1 += dx;
	    y1 += dy;
	    draw_solid_square(st, x1, y1, endwall, st->sgc);
	    st->maze[x1][y1] |= SOLVER_VISIT;
	}
	return 1;
    }
    else
	return 0;
}
