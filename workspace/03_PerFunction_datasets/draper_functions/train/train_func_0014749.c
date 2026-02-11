read64le(uint64 *Bufo, std::istream *is)
{
	uint64 buf;
	if(is->read((char*)&buf,8).gcount() != 8)
		return 0;
#ifdef LSB_FIRST
	*Bufo=buf;
#else
	*Bufo = FCEU_de64lsb((uint8*)&buf);
#endif
	return 1;
}
