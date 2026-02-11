calc_points2(trianglestruct * tp, int d, int *y0_p, int *y1_p, int *y2_p, XPoint * p)
{
	*y0_p = tp->level[MAX(tp->h[tp->i + d][tp->j], 0)];
	*y1_p = tp->level[MAX(tp->h[tp->i + d][tp->j + d], 0)];
	*y2_p = tp->level[MAX(tp->h[tp->i][tp->j + d], 0)];

	p[0].x = tp->xpos[2 * (tp->i + d) + tp->j];
	p[1].x = tp->xpos[2 * (tp->i + d) + (tp->j + d)];
	p[2].x = tp->xpos[2 * tp->i + (tp->j + d)];

	p[0].y = tp->ypos[tp->j] - *y0_p;
	p[1].y = tp->ypos[tp->j + d] - *y1_p;
	p[2].y = tp->ypos[tp->j + d] - *y2_p;
}
