Play(unsigned item) {
	std::set<PlaylistInterface *>::const_iterator i;
	std::set<playlist_interface *>::const_iterator j;


	Lock();

	if(item < 1) item = 1;
	if(item <= queue.size()) {
		curritem = item;
		PlayFile(queue[curritem - 1]);
	} else {
		curritem = queue.size();
		Stop();
	}
	LockInterfaces();

	if(interfaces.size() > 0) {
		for(i = interfaces.begin(); i != interfaces.end(); i++) {
			(*i)->CbSetCurrent(curritem);
		}
	}
	if (cinterfaces.size() > 0) {
		for(j = cinterfaces.begin(); j != cinterfaces.end(); j++) {
			(*j)->cbsetcurrent((*j)->data, curritem);
		}
	}
	UnlockInterfaces();
	Unlock();
}
