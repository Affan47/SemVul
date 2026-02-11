digest64s(XMP_Int64* returnValue, LFA_FileRef file,const std::string key , bool BigEndian  )
{
	*returnValue = digest64s(file,key,BigEndian);
}
