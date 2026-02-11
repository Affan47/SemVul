merge_anno(ByteStream &out)
{


  const GP<ByteStream> str(get_merged_anno());
  if (str)
  {
    str->seek(0);
    if (out.tell())
    {
      out.write((void *) "", 1);
    }
    out.copy(*str);
  }
}
