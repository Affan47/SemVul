encode_line(const char in[], char out[], int len)
{
  *out++ = UUENC(len);

  while (len > 0)
    {
      encode(in, out);
      in += 3;
      out += 4;
      len -= 3;
    }
  *out++ = '\n';
  *out++ = '\0';
}
