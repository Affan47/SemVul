rawunput(c)
int c;
{
  if ( spot >= BUFFSIZE - 1 )
  { buff = my_list_realloc(buff,BUFFSIZE+500,ETERNAL_BLOCK);
    BUFFSIZE += 500;
  }

  buff[spot++] = (char)c;
}
