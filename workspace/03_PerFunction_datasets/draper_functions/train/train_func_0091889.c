put(bostream& file, MD5Sum* md) const {


  uint64 descLen = 4 + 6*2;
  unsigned bufLen = 4 + 6;
  for (const_iterator i = begin(), e = end(); i != e; ++i) {
    unsigned s = (*i)->serialSizeOf();
    bufLen = max(bufLen, s);
    descLen += s;
  }
  if (DEBUG) bufLen += 1;


  byte buf[bufLen];
  if (DEBUG) buf[bufLen - 1] = 0xa5;
  byte* p;
  p = serialize4(0x43534544, buf);
  p = serialize6(descLen, p);
  writeBytes(file, buf, 4 + 6);
  if (md != 0) md->update(buf, 4 + 6);
  for (const_iterator i = begin(), e = end(); i != e; ++i) {
    JigdoDesc::ImageInfo* info;
    JigdoDesc::UnmatchedData* unm;
    JigdoDesc::MatchedFile* matched;
    JigdoDesc::WrittenFile* written;


    if ((info = dynamic_cast<JigdoDesc::ImageInfo*>(*i)) != 0)
      p = info->serialize(buf);
    else if ((unm = dynamic_cast<JigdoDesc::UnmatchedData*>(*i)) != 0)
      p = unm->serialize(buf);
    else if ((written = dynamic_cast<JigdoDesc::WrittenFile*>(*i)) != 0)
      p = written->serialize(buf);
    else if ((matched = dynamic_cast<JigdoDesc::MatchedFile*>(*i)) != 0)
      p = matched->serialize(buf);
    else { Assert(false); continue; }
    writeBytes(file, buf, p - buf);
    if (md != 0) md->update(buf, p - buf);
  }
  p = serialize6(descLen, buf);
  writeBytes(file, buf, 6);
  if (md != 0) md->update(buf, 6);
  if (DEBUG) { Assert(buf[bufLen - 1] == 0xa5); }
  return file;
}
