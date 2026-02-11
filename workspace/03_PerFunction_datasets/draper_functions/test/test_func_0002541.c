check_room_left(n)
size_t n;
{

   if ( (pos + n - strstart) > (int)strsize )
    { size_t len = pos - strstart;
      size_t linespot = linestart - strstart;
      strstart = my_list_realloc(strstart,strsize + 1000 + n,ETERNAL_BLOCK);
      strsize += 1000 + n;
      linestart = strstart + linespot;
      pos = strstart + len;
    }
}
