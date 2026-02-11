gen_web_stream_plus(ushort stream, int pos, int len)
{
   ushort web = 0;
   int i;

   web |= 0x1 << pos;

   for (i=pos-1; i>=0; i--)
     {
      if (stream & (0x1 << i))
	{
	 web |= 0x1 << i;
	 break;
	}
      else
	 web |= 0x1 << i;
     }

   for (i=pos+1; i<len; i++)
     {
      if (stream & (0x1 << i))
	{
	 web |= 0x1 << i;
	 break;
	}
      else
	 web |= 0x1 << i;
     }

   return web;
}
