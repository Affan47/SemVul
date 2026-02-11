makeBall(int w, int h, edgefn ef)
{
    int i, cap;

    makeCylinder (w, h, ef);

    for (i = 1; i <= h; i++)
	ef (0, i);

    cap = w*h+1;
    for (i = (w-1)*h+1; i <= w*h; i++)
	ef (i, cap);

}
