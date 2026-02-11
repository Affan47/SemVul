stopTimer(TimerId id)
{
	TimerList::iterator it = arrTimers.find(id);
	if(it != arrTimers.end()){
		zfree(it->second);
		arrTimers.erase(it);
	}
}
