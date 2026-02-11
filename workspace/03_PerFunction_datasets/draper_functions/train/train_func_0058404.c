make_tform(HPoint3 *p1, HPoint3 *p2, HPoint3 *p3, Transform m)


{
    HPoint3 nv1, nv2;
    Transform trans;

    VSUB3(p2, p1, &nv1);
    VSUB3(p3, p2, &nv2);
    nv1.w = 1.0; nv2.w = 1.0;
    NORMALIZE3(&nv1);
    NORMALIZE3(&nv2);
    if ( !make_rotation(&nv1, &nv2, m))
	{
#ifdef DEBUG
	fprintf(stderr,"Non-independent vectors: make_rotation\n");
#endif
	return(-1);
	}

    TmTranslate(trans, p1->x, p1->y, p1->z);

    TmConcat(m, trans, m);
    return(0);
    }
