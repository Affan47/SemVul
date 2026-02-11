List(std::vector<std::string>& events)
{
	events.clear();

	if (mEventBuffer.size() <= 1) return;

	typedef EventBufferIterator<Buffer::iterator> EventIterator;
	EventIterator eit(mEventBuffer.begin()+1);

	for (ObjRefs::iterator oit = mObjectReferences.begin();
			oit != mObjectReferences.end();
				++oit, ++eit)
	{
		events.push_back(eit.get_name());
	}
}
