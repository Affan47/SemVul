SplineCurve(canvas, pointPtr, numPoints, numSteps, xPoints, dblPoints)
Tk_Canvas canvas;

double *pointPtr;

int numPoints;
int numSteps;


XPoint xPoints[];


double dblPoints[];


{
    int outputPoints, i;


    if ((numPoints < 4) || (numPoints % 3 != 1)) {
	return TkMakeBezierCurve(canvas, pointPtr, numPoints, numSteps,
				 xPoints, dblPoints);
    }


    if (!pointPtr) {
	return (1 + (numPoints / 3) * numSteps);
    }
    outputPoints = 0;
    if (xPoints != NULL) {
	Tk_CanvasDrawableCoords(canvas, pointPtr[0], pointPtr[1],
				&xPoints->x, &xPoints->y);
	xPoints += 1;
    }
    if (dblPoints != NULL) {
	dblPoints[0] = pointPtr[0];
	dblPoints[1] = pointPtr[1];
	dblPoints += 2;
    }
    outputPoints += 1;

    for (i = 2; i < numPoints; i += 3, pointPtr += 6) {
	if (xPoints != NULL) {
	    TkBezierScreenPoints(canvas, pointPtr, numSteps, xPoints);
	    xPoints += numSteps;
	}
	if (dblPoints != NULL) {
	    TkBezierPoints(pointPtr, numSteps, dblPoints);
	    dblPoints += 2 * numSteps;
	}
	outputPoints += numSteps;
    }
    return outputPoints;
}
