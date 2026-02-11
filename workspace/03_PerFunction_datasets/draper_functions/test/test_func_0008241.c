get_text(GP<DjVuFile> file)
{
  GUTF8String chkid;
  GP<IFFByteStream> iff = IFFByteStream::create(get_anno(file));
  while (iff->get_chunk(chkid))
    {
      if (chkid == "TXTa")
        {
          GP<DjVuTXT> txt = DjVuTXT::create();
          txt->decode(iff->get_bytestream());
          return txt;
        }
      else if (chkid == "TXTz")
        {
          GP<DjVuTXT> txt = DjVuTXT::create();
          GP<ByteStream> bsiff = BSByteStream::create(iff->get_bytestream());
          txt->decode(bsiff);
          return txt;
        }
      iff->close_chunk();
    }
  return 0;
}
