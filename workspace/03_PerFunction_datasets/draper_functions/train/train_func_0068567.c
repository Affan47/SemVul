reportProgress(){

	static uint64_t totalTraceLines = memTrace.size();

	int completePercent = ((totalTraceLines-memTrace.size())*100)/totalTraceLines ;
	if(completePercent%10 == 0 && completePercent ){
		std::cerr<<"\r--> "<<completePercent<<"% done"<<flush;
	}
	if(completePercent == 100 )
		std::cerr<<endl;
}
