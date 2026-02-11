writeXML(ByteStream &str_out,const GURL &doc_url,const int flags) const
{
  const int height=get_height();

  static const char *Object="<OBJECT data=\"";
  const GURL url(get_djvu_file()->get_url());
  const GUTF8String pagename(url.fname());
  GUTF8String page_param;
  if(doc_url.is_valid() && !doc_url.is_empty() && (doc_url != url))
  {
    str_out.writestring(Object+doc_url.get_string());
    page_param="<PARAM name=\"PAGE\" value=\""+pagename+"\" />\n";
  }else
  {
    str_out.writestring(Object+doc_url.get_string());
  }
  str_out.writestring("\" type=\""+get_mimetype()+"\" height=\""
    +GUTF8String(height)+"\" width=\""+GUTF8String(get_width())
    +"\" usemap=\""+pagename.toEscaped()+"\" >\n");
  if(!(flags & NOINFO))
  {
    const GP<DjVuInfo> info(get_info());
    if(info)
    {
      info->writeParam(str_out);
    }
  }
  str_out.writestring(page_param);
  const GP<DjVuAnno> anno(DjVuAnno::create());
  if(!(flags & NOINFO)||!(flags&NOMAP))
  {
    const GP<ByteStream> anno_str(get_anno());
    if(anno_str)
    {
      anno->decode(anno_str);
    }
    if(!(flags & NOINFO))
    {
      anno->writeParam(str_out);
    }
  }
  if(!(flags & NOTEXT))
  {
    const GP<DjVuText> text(DjVuText::create());
    {
      const GP<ByteStream> text_str(get_text());
      if(text_str)
      {
        text->decode(text_str);
      }
      text->writeText(str_out,height);
    }
  }
  if(!(flags & NOMETA))
  {
    const GP<ByteStream> meta_str(get_meta());
    if(meta_str)
    {
      GP<IFFByteStream> giff=IFFByteStream::create(meta_str);
      IFFByteStream &iff=*giff;
      GUTF8String chkid;
      while( iff.get_chunk(chkid))
      {
        GP<ByteStream> gbs(iff.get_bytestream());
        if(chkid == "METa")
        {
	   str_out.copy(*gbs);

        }else if(chkid == "METz")
        {
          gbs=BSByteStream::create(gbs);
          str_out.copy(*gbs);

        }
        iff.close_chunk();
      }
    }
  }
  str_out.writestring(GUTF8String("</OBJECT>\n"));
  if(!(flags & NOMAP))
  {
    anno->writeMap(str_out,pagename,height);
  }
}
