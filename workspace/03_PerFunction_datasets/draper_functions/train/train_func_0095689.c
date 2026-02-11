getFileName()
{
	QString ret = mPath.c_str();
	ret += "/";
	ret += sFileName;
	outDebug(4,std::cout << "file name=" << ret.toStdString() << std::endl);
	return ret;
}
