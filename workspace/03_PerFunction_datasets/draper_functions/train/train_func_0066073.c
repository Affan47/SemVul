mob_hasname(struct mobatom *atom,struct atomid *id2)
{ struct atomid id1;

  mob_getid(&id1,atom);
  if (id1.atom==id2->atom&&id1.altloc==id2->altloc) return(1); else return(0); }
