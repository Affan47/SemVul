bonds_are_close (struct Bond *bond1, struct Bond *bond2)
{
  if (bond1->type == BOND_GROUP || bond2->type == BOND_GROUP)
    return 0;

  if (bond1->type >= BOND_ATOM)
    {
      if ((IS_SMALL (bond1->x3 - bond2->x1)
	   && IS_SMALL (bond1->y3 - bond2->y1))
	  || (IS_SMALL (bond1->x3 - bond2->x2)
	      && IS_SMALL (bond1->y3 - bond2->y2)))
	return 1;
    }
  else
    {
      if (bond2->type >= BOND_ATOM)
	{
	  if ((IS_SMALL (bond1->x1 - bond2->x3)
	       && IS_SMALL (bond1->y1 - bond2->y3))
	      || (IS_SMALL (bond1->x2 - bond2->x3)
		  && IS_SMALL (bond1->y2 - bond2->y3)))
	    return 1;
	}
      else
	{
	  if ((IS_SMALL (bond1->x1 - bond2->x1)
	       && IS_SMALL (bond1->y1 - bond2->y1))
	      || (IS_SMALL (bond1->x1 - bond2->x2)
		  && IS_SMALL (bond1->y1 - bond2->y2))
	      || (IS_SMALL (bond1->x2 - bond2->x1)
		  && IS_SMALL (bond1->y2 - bond2->y1))
	      || (IS_SMALL (bond1->x2 - bond2->x2)
		  && IS_SMALL (bond1->y2 - bond2->y2)))
	    return 1;
	}
    }

  return 0;
}
