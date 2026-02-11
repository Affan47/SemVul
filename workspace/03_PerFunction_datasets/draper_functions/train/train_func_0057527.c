AVCHD_PlaylistContainsClip ( LFA_FileRef& mplFileRef, XMP_Uns16& playItemID, const std::string& strClipName )
{

	struct AVCHD_blkPlayList
	{
		XMP_Uns32	mLength;
		XMP_Uns16	mReserved;
		XMP_Uns16	mNumberOfPlayItems;
		XMP_Uns16	mNumberOfSubPaths;
	};

	AVCHD_blkPlayList blkPlayList;
	blkPlayList.mLength = LFA_ReadUns32_BE ( mplFileRef );
	LFA_Read ( mplFileRef, &blkPlayList.mReserved, 2 );
	blkPlayList.mNumberOfPlayItems = LFA_ReadUns16_BE ( mplFileRef );
	blkPlayList.mNumberOfSubPaths = LFA_ReadUns16_BE ( mplFileRef );


	struct AVCHD_blkPlayItem
	{
		XMP_Uns16	mLength;
		char		mClipInformationFileName[5];

	};

	AVCHD_blkPlayItem currPlayItem;
	XMP_Uns64 blockStart = 0;
	for ( playItemID = 0; playItemID < blkPlayList.mNumberOfPlayItems; ++playItemID ) {
		currPlayItem.mLength = LFA_ReadUns16_BE ( mplFileRef );


		blockStart = LFA_Tell ( mplFileRef );
		LFA_Read ( mplFileRef, currPlayItem.mClipInformationFileName, 5 );

		if ( strncmp ( strClipName.c_str(), currPlayItem.mClipInformationFileName, 5 ) == 0 ) return true;

		LFA_Seek ( mplFileRef, blockStart + currPlayItem.mLength, SEEK_SET );
	}

	return false;
}
