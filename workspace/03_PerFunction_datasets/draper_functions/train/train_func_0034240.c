busOnToBddBeh (beh, name)
     befig_list *beh;
     char *name;
{
  bebus_list *bus = beh->BEBUS;
  binode_list *binode;
  pNode res;

  while (bus && strcmp (bus->NAME, name))
    bus = bus->NEXT;

  if (bus == NULL)
    {
      printf ("error : busOnToBdd %s doesn't exist as a bus in %s\n",
	      name, beh->NAME);
      exit (-1);
    }

  res = zero;
  binode = bus->BINODE;
  while (binode)
    {
      res = applyBinBdd (OR, applyBinBdd (AND, binode->VALNODE, binode->CNDNODE), res);
      binode = binode->NEXT;
    }
  return (res);
}
