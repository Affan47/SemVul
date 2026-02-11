revert_window (ScreenInfo * s)
{
  Client *c;

  if (mouse_on_screen () != s)
    {
      if (current && (current->screen == s))
	nofocus ();

      return;
    }

  if (prev_current)
    {
      c = prev_current;

      if (!c->istool && !c->isaside
	  && (DO_TILE (c, s) || DO_RAISE_NOTILE (c, s)))
	{
	  if (c->isnotile)
	    raise_notile (s);
	  else
	    raise_tile (s, 0);

	  active (c);
	  return;
	}
    }

  for (c = clients; c; c = c->next)
    {
      if (!c->istool && !c->isaside
	  && (DO_TILE (c, s) || DO_RAISE_NOTILE (c, s)))
	{
	  if (c->isnotile)
	    raise_notile (s);
	  else
	    raise_tile (s, 0);

	  active (c);
	  return;
	}
    }

  nofocus ();
}
