set_next(int p, int newval)
{
  if (tnoun(p)) noun[p-first_noun].next=newval;
  else if (tcreat(p)) creature[p-first_creat].next=newval;
  else {writeln("INT ERR: Invalid object in chain.");return;}
}
