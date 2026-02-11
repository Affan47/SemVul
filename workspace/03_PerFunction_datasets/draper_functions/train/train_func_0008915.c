send_task(){
	list<Job > templist;
	list<Job *>::iterator i;
        for(i=list2.begin(); i != list2.end(); ++i){
       		templist.push_back(*(*i));
       }
	scheduler->submitJobs(templist);
	list2.clear();
	templist.clear();

 }
