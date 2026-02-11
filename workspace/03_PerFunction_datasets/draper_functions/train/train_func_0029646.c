getNextVector(io::IReadFile* file, core::vector3df& vec, bool binary) const
{
	if (binary)
	{
		file->read(&vec.X, 4);
		file->read(&vec.Y, 4);
		file->read(&vec.Z, 4);
#ifdef __BIG_ENDIAN__
		vec.X = os::Byteswap::byteswap(vec.X);
		vec.Y = os::Byteswap::byteswap(vec.Y);
		vec.Z = os::Byteswap::byteswap(vec.Z);
#endif
	}
	else
	{
		goNextWord(file);
		core::stringc tmp;

		getNextToken(file, tmp);
		core::fast_atof_move(tmp.c_str(), vec.X);
		getNextToken(file, tmp);
		core::fast_atof_move(tmp.c_str(), vec.Y);
		getNextToken(file, tmp);
		core::fast_atof_move(tmp.c_str(), vec.Z);
	}
	vec.X=-vec.X;
}
