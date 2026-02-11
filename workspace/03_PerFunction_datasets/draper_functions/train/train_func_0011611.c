find(const String &pattern, bool recursive, bool dirs) {
	StringVectorPtr ret = StringVectorPtr(new StringVector());

	FileInfoList::iterator i, iend;
	iend = mFileList.end();
	for(i = mFileList.begin(); i != iend; ++i) {
		if(StringUtil::match(i->filename, pattern, true))
			ret->push_back(i->filename);
	}

	return ret;
}
