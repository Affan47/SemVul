bytemap(ino, map1, map2)
of_t ino;
int *map1;
int *map2;
{
	union oc {
		of_t o;
		char c[SOF];
	};
	union oc in;
	union oc out;
	register int i;

	in.o = ino;
	for (i = 0; i < SOF; i++)
		out.c[map2[i]] = in.c[map1[i]];
	return(out.o);
}
