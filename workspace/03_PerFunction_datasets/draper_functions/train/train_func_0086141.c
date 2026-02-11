countup(long *loopcount, long maxcount)
{


  (*loopcount)++;
  if ((*loopcount) >= maxcount) {
    ajErr("Made %ld attempts to read input in loop. Aborting run.",
            *loopcount);
    exxit(-1);
  }
}
