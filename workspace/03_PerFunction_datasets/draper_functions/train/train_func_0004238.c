mem_exitseg(father, mother)
thisperson *father, *mother;
{
  thisperson *child;

  child = father->foff;
  do {
    if (child->ma == mother && (!child->up))
      mem_cleanup(&child);
    child = child->nextpa;
  } while (child != NULL);
}
