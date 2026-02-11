et_edge(
int isx,
int negh,
double mj,
double mi0,
double mi1
) {
	int e, h;
	hedge *he;

	if (mi1 < mi0)
		error ("et_edge, minor coords wern't ordered");

	if ((he = (hedge *)calloc(sizeof(hedge), 1)) == NULL)
		error("Malloc of half edge structure failed");

	for (e = 0; e < 3; e++)
		he->rgb[e] = et.rgb[e];


	if (isx) {
		double tmi0, tmi1;
		tmi0 = et.height - mi1;
		tmi1 = et.height - mi0;
		mi0 = tmi0;
		mi1 = tmi1;
	} else {
		mj = et.height - mj;
	}

	he->negh = negh ? 1 : 0;
	he->mj   = mj;
	he->mi0  = mi0;
	he->mi1  = mi1;


	h = isx ? 0 : 1;
	et.nhe[h]++;
	he->next = et.he[h];
	et.he[h] = he;
}
