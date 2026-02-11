poser_wire1(char layer, long width, char* ins1, char *con1,
	long index1, char* ins2, char* con2,long index2)
{

	if (mode_debug)
		printf("wire1 layer %d width %ld ins1 %s con1 %s index1 %ld ins2 %s con2 %s index2 %ld\n", (int) layer, width,
		     ins1, con1, index1, ins2, con2, index2);

	GENLIB_WIRE1(layer, width, ins1, con1, index1, ins2, con2, index2);
}
