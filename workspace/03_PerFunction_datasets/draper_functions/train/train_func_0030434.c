reshape_fadeplot(ModeInfo * mi, int width, int height)
{
	fadeplotstruct *fp = &fadeplots[MI_SCREEN(mi)];
    fp->width  = width;
    fp->height = height;
	fp->min = MAX(MIN(fp->width, fp->height) / 2, 1);
	fp->factor.x = MAX(fp->width / (2 * fp->min), 1);
	fp->factor.y = MAX(fp->height / (2 * fp->min), 1);
}
