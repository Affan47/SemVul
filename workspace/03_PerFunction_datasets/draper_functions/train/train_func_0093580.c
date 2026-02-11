BeierNeelyMorph(const Image32& source,const Image32& destination,const OrientedLineSegmentPairs& olsp,const float& timeStep,Image32& outputImage){
	OrientedLineSegmentPairs olsp1,olsp2;
	OrientedLineSegment ols;
	Image32 temp1,temp2;
	int i;


	if(!olsp1.setCount(olsp.count) || !olsp2.setCount(olsp.count)){return 0;}
	for(i=0;i<olsp.count;i++){
		olsp1.segments1[i]=olsp.segments1[i];
		olsp2.segments1[i]=olsp.segments2[i];
		OrientedLineSegment::Blend(olsp.segments1[i],olsp.segments2[i],timeStep,ols);
		olsp1.segments2[i]=ols;
		olsp2.segments2[i]=ols;
	}


	if(!source.Warp(olsp1,temp1) || !destination.Warp(olsp2,temp2)){return 0;}


	return CrossDissolve(temp1,temp2,timeStep,outputImage);
}
