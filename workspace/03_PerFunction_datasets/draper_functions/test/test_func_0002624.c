_throw(int x)
{
  int lasty, killed;
  int y, c, last, nextlast, ytop, ybot, ok, doit;


  if (carrying != 0)
    {
      last = 0;
      nextlast = 0;
      lasty = -1;


      for (y = 0; y < HEIGHT; y++)
	{
	  c = blocks[y][x];

	  if (c != 0)
	    {
	      nextlast = last;
	      last = c;
	      lasty = y;
	    }
	}


      ok = NO;

      if (same(last, carrying) == YES)
	{
	  if (same(nextlast, carrying) == YES || howmany > 1)
	    ok = YES;
	}

      doit = YES;

      ybot = lasty + 1 + howmany - 1;


      if (ybot > 10)
	{
	  doit = NO;
	  ybot = 10;
	  if (ok == YES || howmany > 2)
	    doit = YES;
	}


      if (doit == YES)
	{
	  for (y = lasty + 1; y <= ybot; y++)
	    {
	      blocks[y][x] = carrying;
	      drawblock(x, y);
	    }
	}


      ok = NO;

      if (same(last, carrying) == YES)
	{
	  if (same(nextlast, carrying) == YES || howmany > 1)
	    ok = YES;
	}

      if (howmany > 2)
	ok = YES;


      if (ok == YES)
	{
	  ytop = 0;
	  for (y = 0; y <= ybot; y++)
	    {
	      if (blocks[y][x] != carrying)
		ytop = y + 1;
	    }

	  killed = killblock(x, ybot, 1);

	  score = score + scorevals[killed];

	  lines = lines + 1;

	  drawscore();
	  updatelines();
	  playsound(SND_GOT);
	}

      if (doit == YES)
	{
	  carrying = 0;
	  howmany = 0;

	  playsound(SND_THROW);
	}
    }
  else
    {
      complain();
    }


  if (lines >= linesneeded)
    leveldone = YES;
}
