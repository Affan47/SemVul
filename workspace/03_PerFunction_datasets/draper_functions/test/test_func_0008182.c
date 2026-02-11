Cut(Box *set1, Box *set2) {
	BYTE dir;
	int cutr, cutg, cutb;

    LONG whole_r = Vol(set1, mr);
    LONG whole_g = Vol(set1, mg);
    LONG whole_b = Vol(set1, mb);
    LONG whole_w = Vol(set1, wt);

    float maxr = Maximize(set1, FI_RGBA_RED, set1->r0+1, set1->r1, &cutr, whole_r, whole_g, whole_b, whole_w);
	float maxg = Maximize(set1, FI_RGBA_GREEN, set1->g0+1, set1->g1, &cutg, whole_r, whole_g, whole_b, whole_w);
	float maxb = Maximize(set1, FI_RGBA_BLUE, set1->b0+1, set1->b1, &cutb, whole_r, whole_g, whole_b, whole_w);

    if ((maxr >= maxg) && (maxr >= maxb)) {
		dir = FI_RGBA_RED;

		if (cutr < 0) {
			return false;
		}
    } else if ((maxg >= maxr) && (maxg>=maxb)) {
		dir = FI_RGBA_GREEN;
	} else {
		dir = FI_RGBA_BLUE;
	}

	set2->r1 = set1->r1;
    set2->g1 = set1->g1;
    set2->b1 = set1->b1;

    switch (dir) {
		case FI_RGBA_RED:
			set2->r0 = set1->r1 = cutr;
			set2->g0 = set1->g0;
			set2->b0 = set1->b0;
			break;

		case FI_RGBA_GREEN:
			set2->g0 = set1->g1 = cutg;
			set2->r0 = set1->r0;
			set2->b0 = set1->b0;
			break;

		case FI_RGBA_BLUE:
			set2->b0 = set1->b1 = cutb;
			set2->r0 = set1->r0;
			set2->g0 = set1->g0;
			break;
    }

    set1->vol = (set1->r1-set1->r0)*(set1->g1-set1->g0)*(set1->b1-set1->b0);
    set2->vol = (set2->r1-set2->r0)*(set2->g1-set2->g0)*(set2->b1-set2->b0);

    return true;
}
