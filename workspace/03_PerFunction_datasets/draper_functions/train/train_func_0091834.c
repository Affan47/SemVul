sort1_comm_sched(int *sched, int npes, int sortpe, int ascending)
{
     int *sortsched, i;
     sortsched = (int *) MALLOC(npes * sizeof(int) * 2, OTHER);
     fill1_comm_sched(sortsched, sortpe, npes);
     if (ascending)
	  for (i = 0; i < npes; ++i)
	       sortsched[npes + sortsched[i]] = sched[i];
     else
	  for (i = 0; i < npes; ++i)
	       sortsched[2*npes - 1 - sortsched[i]] = sched[i];
     for (i = 0; i < npes; ++i)
	  sched[i] = sortsched[npes + i];
     X(ifree)(sortsched);
}
