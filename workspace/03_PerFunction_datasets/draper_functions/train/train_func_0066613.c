frame2win(frp)
    frame_T	*frp;
{
    while (frp->fr_win == NULL)
	frp = frp->fr_child;
    return frp->fr_win;
}
