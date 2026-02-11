initnet(nnq, thepic, len, sample, colours)
nn_quant *nnq;
unsigned char *thepic;
int len;
int sample;
int colours;
{
	register int i;
	register int *p;


	memset((void*)nnq->network, 0, sizeof(nq_pixel)*MAXNETSIZE);

	nnq->thepicture = thepic;
	nnq->lengthcount = len;
	nnq->samplefac = sample;
	nnq->netsize = colours;

	for (i=0; i < nnq->netsize; i++) {
		p = nnq->network[i];
		p[0] = p[1] = p[2] = p[3] = (i << (netbiasshift+8)) / nnq->netsize;
		nnq->freq[i] = intbias / nnq->netsize;
		nnq->bias[i] = 0;
	}
}
