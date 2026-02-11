parseAudioInfo(MatroskaFile *mf,ulonglong toplen,struct TrackInfo *ti) {
  ulonglong   v;

  FOREACH(mf,toplen)
    case 0xb5:
      ti->AV.Audio.SamplingFreq = readFloat(mf,(unsigned)len);
      break;
    case 0x78b5:
      ti->AV.Audio.OutputSamplingFreq = readFloat(mf,(unsigned)len);
      break;
    case 0x9f:
      v = readUInt(mf,(unsigned)len);
      if (v<1 || v>255)
	errorjmp(mf,"Invalid Channels value");
      ti->AV.Audio.Channels = (unsigned char)v;
      break;
    case 0x7d7b:
      skipbytes(mf,len);
      break;
    case 0x6264:
      v = readUInt(mf,(unsigned)len);
#if 0
      if ((v<1 || v>255) && !IsWritingApp(mf,"AVI-Mux GUI"))
	errorjmp(mf,"Invalid BitDepth: %d",(int)v);
#endif
      ti->AV.Audio.BitDepth = (unsigned char)v;
      break;
  ENDFOR(mf);

  if (ti->AV.Audio.Channels == 0)
    ti->AV.Audio.Channels = 1;
  if (mkv_TruncFloat(ti->AV.Audio.SamplingFreq) == 0)
    ti->AV.Audio.SamplingFreq = mkfi(8000);
  if (mkv_TruncFloat(ti->AV.Audio.OutputSamplingFreq)==0)
    ti->AV.Audio.OutputSamplingFreq = ti->AV.Audio.SamplingFreq;
}
