XDCAMEX_CheckFormat ( XMP_FileFormat format,
						   const std::string & _rootPath,
						   const std::string & gpName,
						   const std::string & parentName,
						   const std::string & _leafName,
						   XMPFiles * parent )
{
	std::string rootPath = _rootPath;
	std::string clipName = _leafName;
	std::string grandGPName;

	std::string bpavPath ( rootPath );


	if ( gpName.empty() != parentName.empty() ) return false;

	if ( gpName.empty() ) {


		bpavPath += kDirChar;
		bpavPath += "BPAV";
		if ( GetChildMode ( bpavPath, "CLPR" ) != kFMode_IsFolder ) return false;

	} else {


		if ( gpName != "CLPR" ) return false;
		SplitLeafName ( &rootPath, &grandGPName );
		MakeUpperCase ( &grandGPName );
		if ( grandGPName != "BPAV" ) return false;
		if ( ! XMP_LitNMatch ( parentName.c_str(), clipName.c_str(), parentName.size() ) ) return false;

		clipName = parentName;

	}


	if ( GetChildMode ( bpavPath, "TAKR" ) != kFMode_IsFolder ) return false;
	if ( GetChildMode ( bpavPath, "MEDIAPRO.XML" ) != kFMode_IsFile ) return false;


	std::string tempPath ( bpavPath );
	tempPath += kDirChar;
	tempPath += "CLPR";
	tempPath += kDirChar;
	tempPath += clipName;
	tempPath += kDirChar;
	tempPath += clipName;
	tempPath += ".MP4";
	if ( GetFileMode ( tempPath.c_str() ) != kFMode_IsFile ) return false;
	tempPath.erase ( tempPath.size()-3 );
	tempPath += "SMI";
	if ( GetFileMode ( tempPath.c_str() ) != kFMode_IsFile ) return false;


	tempPath = rootPath;
	tempPath += kDirChar;
	tempPath += clipName;
	size_t pathLen = tempPath.size() + 1;
	parent->tempPtr = malloc ( pathLen );
	if ( parent->tempPtr == 0 ) XMP_Throw ( "No memory for XDCAMEX clip info", kXMPErr_NoMemory );
	memcpy ( parent->tempPtr, tempPath.c_str(), pathLen );

	return true;

}
