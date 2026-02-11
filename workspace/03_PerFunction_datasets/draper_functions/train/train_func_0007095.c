LoadHeader(FILE *fl)
{
  String header;
  header.readLine(fl);
  if (mystrcasecmp("#word\tdocument id\tflags\tlocation\tanchor", header.get()) == 0)
    return OK;
  else
    return NOTOK;
}
