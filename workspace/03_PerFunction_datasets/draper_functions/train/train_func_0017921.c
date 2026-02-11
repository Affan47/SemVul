tiewind(w, bp)
register Window	*w;
register Buffer	*bp;
{
	bool	not_tied = (w->w_bufp != bp);

	UpdModLine = YES;
	w->w_line = bp->b_dot;
	w->w_char = bp->b_char;
	w->w_bufp = bp;
	if (not_tied)
		CalcWind(w);

}
