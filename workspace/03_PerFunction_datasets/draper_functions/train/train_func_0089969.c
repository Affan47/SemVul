merge(ByteStream & str)
{
   GLParser parser(encode_raw());
   GUTF8String add_raw=read_raw(str);
   parser.parse(add_raw);
   decode(parser);
}
