optUniformLSearch(double *Mh_ptr, double *yk_ptr)
{


	register int	i, j, k;
	int				s, p, dataPoint, pointIndx, lN;
	double			diff, el, dx, dy, tx, weight;


	lN	= N + 2;


	tx = yk_ptr[0] - h[0] + DELTA + 0.99;
	if (tx < 0)
		LowerBoundX = 0;
	else
		LowerBoundX = (int) tx;
	tx = yk_ptr[1] - h[0] + DELTA + 0.99;
	if (tx < 0)
		LowerBoundY = 0;
	else
		LowerBoundY = (int) tx;
	tx = yk_ptr[0] + h[0] - DELTA;
	if (tx >= width)
		UpperBoundX = width-1;
	else
		UpperBoundX = (int) tx;
	tx = yk_ptr[1] + h[0] - DELTA;
	if (tx >= height)
		UpperBoundY = height - 1;
	else
		UpperBoundY = (int) tx;


	for(i = LowerBoundY; i <= UpperBoundY; i++)
		for(j = LowerBoundX; j <= UpperBoundX; j++)
		{


			pointIndx	= i*width+j;
			dataPoint	= N*(pointIndx);


			k		= 1;
			s		= 0;
			dx      = j - yk_ptr[0];
			dy      = i - yk_ptr[1];
			diff	= (dx*dx+dy*dy)/(h[0]*h[0]);
			while((diff < 1.0)&&(k != kp))
			{

				diff = 0;
				for(p = 0; p < P[k]; p++)
				{
					el    = (data[dataPoint+p+s]-yk_ptr[p+s+2])/h[k];
					if((!p)&&(yk_ptr[2] > 80))
						diff += 4*el*el;
					else
					   diff += el*el;
				}


				s += P[k];
				k++;
			}


			if(diff < 1.0)
			{
				weight = 1 - weightMap[i*width+j];
				Mh_ptr[0] += weight*j;
				Mh_ptr[1] += weight*i;
				for(k = 2; k < lN; k++)
					Mh_ptr[k] += weight*data[dataPoint+k-2];
				wsum += weight;


            if (diff < 0.5)
            {
				   if(modeTable[pointIndx] == 0)
				   {
   					pointList[pointCount++]	= pointIndx;
					   modeTable[pointIndx]	= 2;
				   }
            }

			}


		}


		return;

}
