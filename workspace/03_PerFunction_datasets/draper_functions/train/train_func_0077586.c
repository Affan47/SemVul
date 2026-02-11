success(const vector<size_t> &found)
{
	try {
		if (found.size() > 0)
			me->successArray.push_back(me->uid);
		me->nextSearch();
	} catch (...) {
		fail("Exception occured during a search.");
	}
}
