CheckFreeDiskSpace( uint64 neededSpace )
{
	uint64 free = CPath::GetFreeSpaceAt(GetFilePath());
	if (free == static_cast<uint64>(wxInvalidOffset)) {

		return false;
	}


	if ( free < PARTSIZE ) {


		return false;
	}


	if ( thePrefs::IsCheckDiskspaceEnabled() ) {
		neededSpace += thePrefs::GetMinFreeDiskSpace();


		return free >= neededSpace;
	}

	return true;
}
