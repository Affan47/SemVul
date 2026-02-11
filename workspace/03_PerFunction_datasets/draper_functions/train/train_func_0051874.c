blockparse()
{
  CLAUSE *root, *ptr;

  root = (CLAUSE *)NULL;

  if (symbol != beginsym)
    error("if|while|function: missing block open symbol.\n");

  scan();

  if (symbol == nullsym)
  {
    dogets(str, PMODE_BLOCK);
    scan();
  }

  if (symbol != endsym)
  {
    root = ptr = parse();
    while(LINK(ptr) != NULL)
    {
      ptr = LINK(ptr);
    }
  }

  while(symbol != endsym && symbol != elsesym)
  {
    if (symbol == nullsym)
    {
      dogets(str, PMODE_BLOCK); scan();
    }
    if (symbol != endsym && symbol != elsesym)
    {
      LINK(ptr) = parse();
      while(LINK(ptr) != NULL)
      {
        ptr = LINK(ptr);
      }
    }
  }

  bendsym = symbol;
  scan();

  return root;
}
