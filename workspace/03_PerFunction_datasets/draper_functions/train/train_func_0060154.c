gsd_draw_gyro(float *center, unsigned long colr, float siz)
{
    int i;

    gsd_pushmatrix();
    gsd_translate(center[X], center[Y], center[Z]);
    gsd_scale(siz, siz, siz);
    gsd_color_func(colr);


    gsd_bgnline();
    gsd_vert_func(Octo[2]);
    gsd_vert_func(Octo[5]);
    gsd_endline();


    gsd_pushmatrix();

    for (i = 0; i < 6; i++) {
	gsd_rot(30., 'z');
	gsd_bgnline();
	gsd_vert_func(Octo[0]);
	gsd_vert_func(Octo[3]);
	gsd_endline();
    }

    gsd_popmatrix();

    gsd_color_func(colr);

    gsd_circ(0., 0., 1.);

    gsd_pushmatrix();
    gsd_rot(90., 'x');
    gsd_circ(0., 0., 1.);
    gsd_popmatrix();

    gsd_pushmatrix();
    gsd_rot(90., 'y');
    gsd_circ(0., 0., 1.);
    gsd_popmatrix();

    gsd_popmatrix();

    return;
}
