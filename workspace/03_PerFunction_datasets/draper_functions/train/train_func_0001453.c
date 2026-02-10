IsPDF(const unsigned char *magick,const size_t offset)
{
  if (offset < 5)
    return(False);
  if (LocaleNCompare((char *) magick,"%PDF-",5) == 0)
    return(True);
  return(False);
}
