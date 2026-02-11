add_modulos (void)
{
	int m1, m2;

	if (fmode & 0x4000) {
		if (((diwstrt >> 8) ^ vpos) & 1)
			m1 = m2 = bpl2mod;
		else
			m1 = m2 = bpl1mod;
	} else {
		m1 = bpl1mod;
		m2 = bpl2mod;
	}

	switch (bplcon0_planes_limit) {
#ifdef AGA
	case 8: bplpt[7] += m2; bplptx[7] += m2;
	case 7: bplpt[6] += m1; bplptx[6] += m1;
#endif
	case 6: bplpt[5] += m2; bplptx[5] += m2;
	case 5: bplpt[4] += m1; bplptx[4] += m1;
	case 4: bplpt[3] += m2; bplptx[3] += m2;
	case 3: bplpt[2] += m1; bplptx[2] += m1;
	case 2: bplpt[1] += m2; bplptx[1] += m2;
	case 1: bplpt[0] += m1; bplptx[0] += m1;
	}
}
