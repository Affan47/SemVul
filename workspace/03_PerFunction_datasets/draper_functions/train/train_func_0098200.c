kwsysMD5_Append(kwsysMD5* md5, unsigned char const* data, int length)
{
  if(length < 0)
    {
    length = (int)strlen((char const*)data);
    }
  md5_append(&md5->md5_state, (md5_byte_t const*)data, (size_t)length);
}
