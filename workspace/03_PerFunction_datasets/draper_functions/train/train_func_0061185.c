status_x(WINDOW *stswin, int cell)
{
    return (15 * (cell / getmaxy(stswin)));
}
