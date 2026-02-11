ChangeMeta(
  DjVuFile &dfile, const lt_XMLTags &tags )
{
  dfile.resume_decode(true);
  GP<ByteStream> gbs(ByteStream::create());
  tags.write(*gbs,false);
  gbs->seek(0L);
  GUTF8String raw(gbs->getAsUTF8());
  if(raw.length())
  {

    dfile.change_meta(raw+"\n");
  }else
  {
    dfile.change_meta(GUTF8String());
  }
}
