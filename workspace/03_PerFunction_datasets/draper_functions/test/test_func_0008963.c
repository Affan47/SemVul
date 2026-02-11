dumpToConsole(std::ostream &o) const
{
	mrpt::utils::CMemoryStream memStr;
	this->dumpToStream( memStr );
	if (memStr.getTotalBytesCount()) {
		o.write((const char*)memStr.getRawBufferData(),memStr.getTotalBytesCount());
	}
}
