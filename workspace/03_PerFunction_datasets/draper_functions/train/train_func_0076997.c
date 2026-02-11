parseSeekEntry(MatroskaFile *mf,ulonglong toplen) {
  int	    seekid = 0;
  ulonglong pos = (ulonglong)-1;

  FOREACH(mf,toplen)
    case 0x53ab:
      if (len>EBML_MAX_ID_LENGTH)
	errorjmp(mf,"Invalid ID size in parseSeekEntry: %d\n",(int)len);
      seekid = (int)readUInt(mf,(unsigned)len);
      break;
    case 0x53ac:
      pos = readUInt(mf,(unsigned)len);
      break;
  ENDFOR(mf);

  if (pos == (ulonglong)-1)
    errorjmp(mf,"Invalid element position in parseSeekEntry");

  pos += mf->pSegment;
  switch (seekid) {
    case 0x114d9b74:
      if (mf->pSeekHead)
	errorjmp(mf,"SeekHead contains more than one SeekHead pointer");
      mf->pSeekHead = pos;
      break;
    case 0x1549a966:
      mf->pSegmentInfo = pos;
      break;
    case 0x1f43b675:
      if (!mf->pCluster)
	mf->pCluster = pos;
      break;
    case 0x1654ae6b:
      mf->pTracks = pos;
      break;
    case 0x1c53bb6b:
      mf->pCues = pos;
      break;
    case 0x1941a469:
      mf->pAttachments = pos;
      break;
    case 0x1043a770:
      mf->pChapters = pos;
      break;
    case 0x1254c367:
      mf->pTags = pos;
      break;
  }
}
