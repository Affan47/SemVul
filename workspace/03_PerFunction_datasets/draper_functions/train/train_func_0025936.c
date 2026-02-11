pubseekoff(std::streamoff offIn, std::ios_base::seekdir way, std::ios_base::openmode which)
{
	if(is_open() && way!=std::ios_base::end)
	{
		if((which==std::ios_base::in && this->mode & std::ios::in) ||
			(which==std::ios_base::out && this->mode & std::ios::out &&
			((way==std::ios_base::cur && offIn>=0) ||
				(way==std::ios_base::beg && static_cast<z_off_t>(offIn)>=gztell(this->file)))))
		{
			z_off_t off=gzseek(this->file,static_cast<z_off_t>(offIn),(way==std::ios_base::beg?SEEK_SET:SEEK_CUR));
			if(which==std::ios_base::in)
				setg(buffer+buf4,buffer+buf4,buffer+buf4);
			return off;
		}
		else return static_cast<std::streampos>(gztell(this->file));
	}
	return -1;
}
