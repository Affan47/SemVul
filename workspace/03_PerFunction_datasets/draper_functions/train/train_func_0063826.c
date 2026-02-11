NotifyModified(DocModification mh) {
	if (mh.modificationType & SC_MOD_INSERTTEXT) {
		decorations.InsertSpace(mh.position, mh.length);
	} else if (mh.modificationType & SC_MOD_DELETETEXT) {
		decorations.DeleteRange(mh.position, mh.length);
	}
	for (std::vector<WatcherWithUserData>::iterator it = watchers.begin(); it != watchers.end(); ++it) {
		it->watcher->NotifyModified(this, mh, it->userData);
	}
}
