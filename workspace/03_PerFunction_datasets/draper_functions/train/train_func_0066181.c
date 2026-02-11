copyFromForceLoad(const CImage &o)
{
	if (o.isExternallyStored())
	{

		if (!this->loadFromFile( o.getExternalStorageFileAbsolutePath() ))
			THROW_TYPED_EXCEPTION_CUSTOM_MSG1("Error loading externally-stored image from: %s", o.getExternalStorageFileAbsolutePath().c_str() ,CExceptionExternalImageNotFound);
	}
	else
	{
		*this = o;
	}
}
