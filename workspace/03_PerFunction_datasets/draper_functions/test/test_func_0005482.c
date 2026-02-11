subsegtraverse(struct mesh *m)
#else
subseg *subsegtraverse(m)
struct mesh *m;
#endif

{
  subseg *newsubseg;

  do {
    newsubseg = (subseg *) traverse(&m->subsegs);
    if (newsubseg == (subseg *) NULL) {
      return (subseg *) NULL;
    }
  } while (deadsubseg(newsubseg));
  return newsubseg;
}
