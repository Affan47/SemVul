dds_init_pseudocycloid(void)
{
	int i;
	double t;

	for(i=0;i<WAVEFORM_LEN/2;i++){
		t=2*((double)i)/WAVEFORM_LEN;
		waveform[i]=rint(offset+amplitude*sqrt(1-4*t*t));
	}
	for(i=WAVEFORM_LEN/2;i<WAVEFORM_LEN;i++){
		t=2*(1-((double)i)/WAVEFORM_LEN);
		waveform[i]=rint(offset+amplitude*sqrt(1-t*t));
	}
}
