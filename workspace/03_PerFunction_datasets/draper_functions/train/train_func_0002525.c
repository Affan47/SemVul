Register(PlaylistInterface * pl_if) {
	LockInterfaces();
	interfaces.insert(pl_if);

	pl_if->CbClear();
	if(queue.size()) {
		pl_if->CbInsert(queue, 0);
	}
	pl_if->CbSetCurrent(curritem);
	UnlockInterfaces();
}
