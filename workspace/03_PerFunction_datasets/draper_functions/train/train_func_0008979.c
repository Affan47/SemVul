setdata(ObjectStream &s)
{
	int c = GETX_INT32D(s, NULL);
	if (c == VC_TRANSPARENT) {
		color = -1;
	} else {
		for (int i=0; i<16; i++) if (vcs[i]==c) {
			color=i;
			break;
		}
	}
	dirtyview();
}
