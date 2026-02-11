updateMetaDataOnPageInsert(const cacheAtom value)
{

	assert(memTrace.size());
	uint32_t status=0;
	uint32_t currLine = value.getLineNo();
	assert( currLine == memTrace.front().lineNo );
	assert( meta.BlkID == value.getSsdblkno() );
	bool assignedFirstBlkRef = false;
	bool pageAccessInfutureWindow = false;


	set<uint64_t> uniqSet;
	pair<set<uint64_t>::iterator,bool> ret;
	deque<reqAtom>::iterator it = memTrace.begin();
	it++ ;

	for( ; it != memTrace.end() ;  it++ ){
		uint64_t tempFsblkno = it->fsblkno;
		uint32_t tempLineNo = it->lineNo;
		uint64_t tempSsdblkno = it->ssdblkno;
		assert(tempFsblkno && tempLineNo);
		ret=uniqSet.insert(tempFsblkno );
		assert( ret.first != uniqSet.end() );
		assert(  currLine <= tempLineNo );
		if(tempSsdblkno == meta.BlkID ){
			if(assignedFirstBlkRef == false){
				assert(uniqSet.size());
				meta.distance= tempLineNo;
				assignedFirstBlkRef = true;
				IFHIST(_gConfiguration.birdHist[uniqSet.size()]++; );
			}
			if(tempFsblkno == value.getFsblkno() ){
				pageAccessInfutureWindow = true;
				IFHIST(_gConfiguration.pirdHist[uniqSet.size()]++; );
				break;
			}
		}

		if(uniqSet.size() >= ( _gConfiguration.futureWindowSize - 1) ){

			break;
		}
	}

	uniqSet.clear();

	if(pageAccessInfutureWindow == false){
		ret = coldPageSet.insert(value.getFsblkno());
		if( ret.second == false ){
			PRINTV( logfile<<"\tpage "<< value.getFsblkno() <<" was already cold" << endl; );
			status = COLD2COLD;
		}
	}
	else{
		set<uint64_t>::iterator setit;
		setit =  coldPageSet.find(value.getFsblkno());
		if(setit != coldPageSet.end() ){
			PRINTV( logfile<<"\tpage "<< value.getFsblkno() <<" was cold and now is convert to hot" << endl; );
			coldPageSet.erase(setit);
			status = COLD2HOT;
		}
	}
	meta.coldPageCounter = coldPageSet.size();

	if(assignedFirstBlkRef == false){
		assert(pageAccessInfutureWindow == false);
		meta.distance = INF;
	}

	assert( meta.distance );
	return status;
}
