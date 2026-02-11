GetNextChild ( std::string * childName )
	{
		struct dirent * childInfo = 0;

		if ( this->dirRef == 0 ) XMP_Throw ( "XMP_FolderInfo::GetNextChild - not open", kXMPErr_InternalFailure );

		while ( true ) {

			childInfo = readdir ( this->dirRef );
			if ( childInfo == 0 ) return false;
			if ( *childInfo->d_name != '.' ) break;
		}

		*childName = childInfo->d_name;
		return true;

	}
