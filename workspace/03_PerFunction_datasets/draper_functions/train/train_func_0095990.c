get_text(
  const GP<DjVuFile> & file, const GP<ByteStream> &gstr_out)
{
  DEBUG_MSG("DjVuFile::get_text()\n");
  ByteStream &str_out=*gstr_out;
  if (!file->is_data_present() ||
      (file->is_modified() && file->text))
    {

      GCriticalSectionLock lock(&file->text_lock);
      if (file->text && file->text->size())
	{
	  if (str_out.tell())
	    {
	      str_out.write((void *) "", 1);
	    }
	  file->text->seek(0);
	  str_out.copy(*file->text);
	}
    } else if (file->is_data_present())
    {


      const GP<ByteStream> str=file->data_pool->get_stream();
      const GP<IFFByteStream> giff=IFFByteStream::create(str);
      IFFByteStream &iff=*giff;
      GUTF8String chkid;
      if (iff.get_chunk(chkid))
	{
	  while(iff.get_chunk(chkid))
	    {
	      if (is_text(chkid))
		{
		  if (str_out.tell())
		    {
		      str_out.write((void *) "", 1);
		    }
		  const GP<IFFByteStream> giff_out(IFFByteStream::create(gstr_out));
		  IFFByteStream &iff_out=*giff_out;
		  iff_out.put_chunk(chkid);
		  iff_out.copy(*iff.get_bytestream());
		  iff_out.close_chunk();
		}
	      iff.close_chunk();
	    }
	}
      file->data_pool->clear_stream();
    }
}
