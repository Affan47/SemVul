decode(const GP<ByteStream> &gstr)
{

  GP<ByteStream> gpBSByteStream = BSByteStream::create(gstr);
  GCriticalSectionLock lock(&class_lock);
  bookmark_list.empty();
  int nbookmarks=gpBSByteStream->read16();
  if (nbookmarks)
    {
      for(int bookmark=0;bookmark<nbookmarks;bookmark++)
        {
          GP<DjVuBookMark> pBookMark=DjVuBookMark::create();
          pBookMark->decode(gpBSByteStream);
          bookmark_list.append(pBookMark);
        }
    }
}
