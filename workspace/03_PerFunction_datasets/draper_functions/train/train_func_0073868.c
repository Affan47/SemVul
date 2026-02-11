get_data_from_file(const char *cmd, ParsingByteStream &pbs, ByteStream &out)
{
  GUTF8String fname = pbs.get_token();

  if (! fname)
    {
      vprint("%s: enter data and terminate with a period on a single line", cmd);
      int c = pbs.get_spaces(true);
      pbs.unget(c);
      char skip[4];
      char term0[4] = "\n.\n";
      char term1[4] = "\r.\r";
      char *s = skip;
      int state = 1;
      while (state < 3)
        {
          c = pbs.get();
          if (c == EOF)
            break;
          if ( c == term0[state] || c == term1[state] )
            {
              state += 1;
              *s++ = c;
            }
          else
            {
              {
                for (char *m=skip; m<s; m++)
                  out.write8(*m);
              }
              s = skip;
              state = 0;
              if (c == '\n')
                pbs.unget(c);
              else if (c != EOF)
                out.write8(c);
            }
        }
      pbs.unget(c);
    }
  else
    {
      GP<ByteStream> in=ByteStream::create(GURL::Filename::UTF8(fname),"rb");
      out.copy(*in);
    }
}
