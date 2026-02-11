write(ByteStream &str, const char *format, ...)
{


  va_list args;
  va_start(args, format);
  GUTF8String tmp;
  tmp.vformat(format, args);
  str.writall((const char *) tmp, tmp.length());
}
