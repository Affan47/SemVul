find_breakpoint(int breaknum)
{
  breakpoint *p;
  LEsearch(breaklist, p, p->number == breaknum);

  if(p)
    return p;

  infix_print_string("No breakpoint number ");
  infix_print_number(breaknum);
  infix_print_string(".\n");
  return NULL;
}
