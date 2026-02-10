uniform ()
    {

	double p1 = a12 * Cg[1] - a13n * Cg[0];
	int k = p1 / m1;
	p1 -= k * m1;
	if (p1 < 0.0)
	    p1 += m1;
	Cg[0] = Cg[1];
	Cg[1] = Cg[2];
	Cg[2] = p1;


	double p2 = a21 * Cg[5] - a23n * Cg[3];
	k = p2 / m2;
	p2 -= k * m2;
	if (p2 < 0.0)
	    p2 += m2;
	Cg[3] = Cg[4];
	Cg[4] = Cg[5];
	Cg[5] = p2;


	return ((p1 > p2) ? (p1 - p2) * norm : (p1 - p2 + m1) * norm);
    }
