fft_setup (int samps, int speed)
{

	gdk_gc_set_line_attributes (gc_center_line, 1,
		GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);

	if (samps > 3000)
	gdk_gc_set_line_attributes (gc_tune_line, 2,
		GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
	else
	gdk_gc_set_line_attributes (gc_tune_line, 1,
                GDK_LINE_SOLID, GDK_CAP_ROUND, GDK_JOIN_ROUND);
	static int fftspeed=0;
	if(samps>0) {
		samples = samps;
	}
	float expo = 8+(100-speed)/99.0*3;
	    fftspeed = (int)pow(2.0, expo);

	ffts = samples/2;
	deltaf = (float)8000 / samples;

	delta = (int)(fc / deltaf - SPECTRUM_WIDTH/2);
	cnt = 0;
	commControl(COMM_FFTCH, COMM_FFTN, samples);
	commControl(COMM_FFTCH, COMM_FFTOVERLAP, fftspeed);
}
