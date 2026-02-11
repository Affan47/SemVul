setData(int Xcomp, int Ycomp)
{
    bhpointIterator i;

    IOBlackBox->subsetForBH(allPoints, Xcomp, Ycomp, minXval, minYval, maxXval, maxYval);
    dbgprintf("Collected %d points, minX = %g, minY = %g\n"
	      "                     maxX = %g, maxY = %g\n",
	      allPoints.size(),
	      minXval, minYval,
	      maxXval, maxYval);


    dataIsInteger = true;
    for (i = allPoints.begin(); i < allPoints.end(); i += 101) {
	if ((floor((*i).Xvalue) != (*i).Xvalue)
	    || (floor((*i).Yvalue) != (*i).Yvalue)) {
	    dataIsInteger = false;
	    break;
	}
    }
    if (dataIsInteger)
	dbgprintf("Data is integer\n");
    else
	dbgprintf("Data is floating point\n");


	std::sort(allPoints.begin(), allPoints.end(), cmpBHPoints());

    return;
}
