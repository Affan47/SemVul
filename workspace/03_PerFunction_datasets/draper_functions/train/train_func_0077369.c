findChainEnd(const CoordinateSequence* pts,int start){

	int chainQuad=Quadrant::quadrant(pts->getAt(start),pts->getAt(start + 1));
	int last=start+1;
	while(last<(int)pts->getSize()) {

		int quad=Quadrant::quadrant(pts->getAt(last - 1),pts->getAt(last));
		if (quad!=chainQuad) break;
		last++;
	}
	return last-1;
}
