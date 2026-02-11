dump_block(istream *s, int addr)
{
  int c, x;
  bool end;

  c = s->get();
  if (c == EOF)
    {
      end = true;
      return false;
    }

  cout << "Block " << hex << setw(2) << setfill('0')
       << (c & 0xff) << "h (" << dec << (c & 0xff) << ")"
       << endl;

  end = false;
  for (int a = 0;a < 8;a++)
    {
      int c;
      char buf[16];

      cout << hex << setw(4) << setfill('0') << (addr + a * 16) << "h: ";
      x = 16;
      for (int b = 0;b < 16;b++)
        {
          c = s->get();
          if (c == EOF)
            {
              x = b;
              end = true;
              break;
            }
          buf[b] = c;
        }
      for (int b = 0;b < 16;b++)
        {
	  if (b == 8)
	    cout << "- ";
          if (b >= x)
            cout << "   ";
          else
	    cout << hex << setw(2) << setfill('0') << (buf[b] & 0xff) << " ";
        }
      cout << "| ";
      for (int b = 0;b < 16;b++)
        {
          if (b >= x)
            break;
          cout << (char)(isprint(buf[b]) ? buf[b] : '.');
        }
      cout << endl;
      if (end)
        break;
    }
  cout << endl;

  return !end;
}
