findRGBExtremes(double x0[3], double y0[3], double x1[3], double y1[3],
				       double startX[3], double startY[3],
				       double endX[3], double endY[3])
{

    double    swapd;

    for (int i = 0 ; i < 3 ; ++i) {

	if (x0[i] > x1[i] || y0[i] > y1[i]) {
	    swapd = x0[i];
	    x0[i] = x1[i];
	    x1[i] = swapd;
	    if (y0[i] > 1) {
		startX[i] = x0[i];
		startY[i] = 1.0;
	    } else {
		startX[i] = 0.0;
		startY[i] = y0[i];
	    }
	    if (y1 > 0) {
		endX[i] = 1.0;
		endY[i] = y1[i];
	    } else {
		endX[i] = x1[i];
		endY[i] = 0.0;
	    }
	} else {
	    if (y0[i] < 0)  {
		startX[i] = x0[i];
		startY[i] = 0.0;
	    } else {
		startX[i] = 0.0;
		startY[i] = y0[i];
	    }
	    if (y1[i] <= 1) {
		endX[i] = 1.0;
		endY[i] = y1[i];
	    } else {
		endX[i] = x1[i];
		endY[i] = 1.0;
	    }
	}
    }

    return;
}
