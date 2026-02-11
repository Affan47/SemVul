SonyHDV_CheckFormat ( XMP_FileFormat format,
						   const std::string & rootPath,
						   const std::string & gpName,
						   const std::string & parentName,
						   const std::string & leafName,
						   XMPFiles * parent )
{


	if ( gpName.empty() != parentName.empty() ) return false;

	std::string tempPath = rootPath;
	tempPath += kDirChar;
	tempPath += "VIDEO";

	if ( gpName.empty() ) {

		if ( GetChildMode ( tempPath, "HVR" ) != kFMode_IsFolder ) return false;
	} else {

		if ( (gpName != "VIDEO") || (parentName != "HVR") ) return false;
	}


	tempPath += kDirChar;
	tempPath += "HVR";

	std::string clipName = leafName;
	int usCount = 0;
	size_t i, limit = leafName.size();
	for ( i = 0; i < limit; ++i ) {
		if ( clipName[i] == '_' ) {
			++usCount;
			if ( usCount == 2 ) break;
		}
	}
	if ( i < limit ) clipName.erase ( i );
	clipName += '_';

	XMP_FolderInfo folderInfo;
	std::string childName;
	bool found = false;

	folderInfo.Open ( tempPath.c_str() );
	while ( (! found) && folderInfo.GetNextChild ( &childName ) ) {
		size_t childLen = childName.size();
		if ( childLen < 4 ) continue;
		MakeUpperCase ( &childName );
		if ( childName.compare ( childLen-4, 4, ".IDX" ) != 0 ) continue;
		if ( childName.compare ( 0, clipName.size(), clipName ) == 0 ) {
			found = true;
			clipName = childName;
			clipName.erase ( childLen-4 );
		}
	}
	if ( ! found ) return false;


	clipName = leafName;


	tempPath = rootPath;
	tempPath += kDirChar;
	tempPath += clipName;

	size_t pathLen = tempPath.size() + 1;
	parent->tempPtr = malloc ( pathLen );
	if ( parent->tempPtr == 0 ) XMP_Throw ( "No memory for SonyHDV clip info", kXMPErr_NoMemory );
	memcpy ( parent->tempPtr, tempPath.c_str(), pathLen );

	return true;

}
