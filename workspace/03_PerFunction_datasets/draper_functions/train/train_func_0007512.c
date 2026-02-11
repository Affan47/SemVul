getSharpness (BYTE* img, int width, int height, int t)
{
	float res=0;
	int numMCUx = width/(8*2);
	int numMCUy = height/(8*2);
	INT16 dataMCU[64];
	INT16* data;
	INT16 dataY[width*height];
	INT16 *Y = dataY;

	double weight;
	double xp_;
	double yp_;
	int ctx = numMCUx >> 1;
	int cty = numMCUy >> 1;
	double rad=ctx/2;
	if (cty<ctx) { rad=cty/2; }
	rad=rad*rad;
	int cnt2 =0;

	data=dataMCU;

	Y = extractY (img, Y, width, height);

	int i=0;
	int j=0;
	int xp=0;
	int yp=0;

	for (yp=0;yp<numMCUy;yp++)
	{
		yp_=yp-cty;
    		for (xp=0;xp<numMCUx;xp++)
		{
			xp_=xp-ctx;
			weight = exp(-(xp_*xp_)/rad-(yp_*yp_)/rad);
			for (i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{

					dataMCU[i*8+j]=Y[(((height-(numMCUy-(yp*2))*8)>>1)+i)*width
						+(((width-(numMCUx-(xp*2))*8)>>1)+j)];
				}
			}
			getSharpnessMCU(data,weight);
			cnt2++;
		}
	}

	for (i=0;i<=t;i++)
	{
		for(j=0;j<t;j++)
		{
			sumAC[i*8+j]/=(double) (cnt2);
			res+=sumAC[i*8+j]*ACweight[i*8+j];
		}
	}
	return (roundf(res*10));
}
