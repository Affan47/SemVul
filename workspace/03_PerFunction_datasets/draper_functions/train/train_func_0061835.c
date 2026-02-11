Next() {
	std::set<PlaylistInterface *>::const_iterator i;
	std::set<playlist_interface *>::const_iterator j;

	Lock();

	unsigned olditem = curritem;
	if(queue.size() > 0) {
	  if(curritem < queue.size()) {
	      curritem++;
	      PlayFile(queue[curritem - 1]);
	  } else if (curritem == queue.size()){
	    if (LoopingPlaylist()){
	      curritem = 1;
	      PlayFile(queue[curritem -1]);
	    } else {
		    Stop();
	    }
	  }
	}


	if (curritem != olditem) {
		if (interfaces.size() > 0) {
			for (i = interfaces.begin(); i != interfaces.end(); i++) {
				(*i)->CbSetCurrent(curritem);
			}
		}
		if (cinterfaces.size() > 0) {
			for (j = cinterfaces.begin(); j != cinterfaces.end(); j++) {
				(*j)->cbsetcurrent((*j)->data, curritem);
			}
		}
	}
	Unlock();
}
