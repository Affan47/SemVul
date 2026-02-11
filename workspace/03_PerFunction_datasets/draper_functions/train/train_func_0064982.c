codeBreakpointBetween(unsigned int start, unsigned int end)
{
    int i;

    i = 0;
    while (!bp[i].last)
      {
	  if ((bp[i].address >= start && bp[i].address < end) &&
	      (bp[i].type == CODE) && bp[i].enabled)
	      return true;

	  i++;
      }

    return false;
}
