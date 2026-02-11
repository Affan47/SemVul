ReadAVCHDPlaylistMarkExtension ( LFA_FileRef& mplFileRef,
											 XMP_Uns16 playlistMarkID,
											 AVCHD_blkPlayListMarkExt& avchdLegacyData )
{
	avchdLegacyData.mLength = LFA_ReadUns32_BE ( mplFileRef );

	if ( avchdLegacyData.mLength == 0 ) return false;

	avchdLegacyData.mNumberOfPlaylistMarks = LFA_ReadUns16_BE ( mplFileRef  );

	if ( avchdLegacyData.mNumberOfPlaylistMarks <= playlistMarkID ) return true;


	const XMP_Uns64 markExtensionSize = 66;


	const XMP_Uns64 markOffset = markExtensionSize * playlistMarkID;

	avchdLegacyData.mPresent = 1;
	LFA_Seek ( mplFileRef, markOffset, SEEK_CUR );
	avchdLegacyData.mMakerID = LFA_ReadUns16_BE ( mplFileRef );
	avchdLegacyData.mMakerModelCode = LFA_ReadUns16_BE ( mplFileRef  );
	LFA_Read ( mplFileRef, &avchdLegacyData.mReserved1, 3 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mFlags, 1 );
	avchdLegacyData.mRefToMarkThumbnailIndex = LFA_ReadUns16_BE ( mplFileRef  );
	LFA_Read ( mplFileRef, &avchdLegacyData.mBlkTimezone, 1 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mRecordDataAndTime, 7 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mMarkCharacterSet, 1 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mMarkNameLength, 1 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mMarkName, 24 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mMakersInformation, 16 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mBlkTimecode, 4 );
	LFA_Read ( mplFileRef, &avchdLegacyData.mReserved2, 2 );

	return true;
}
