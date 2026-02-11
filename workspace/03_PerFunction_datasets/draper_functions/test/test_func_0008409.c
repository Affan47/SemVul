fill1_comm_sched(int *sched, int which_pe, int npes)
{
     int pe, i, n, s = 0;
     A(which_pe >= 0 && which_pe < npes);
     if (npes % 2 == 0) {
	  n = npes;
	  sched[s++] = which_pe;
     }
     else
	  n = npes + 1;
     for (pe = 0; pe < n - 1; ++pe) {
	  if (npes % 2 == 0) {
	       if (pe == which_pe) sched[s++] = npes - 1;
	       else if (npes - 1 == which_pe) sched[s++] = pe;
	  }
	  else if (pe == which_pe) sched[s++] = pe;

	  if (pe != which_pe && which_pe < n - 1) {
	       i = (pe - which_pe + (n - 1)) % (n - 1);
	       if (i < n/2)
		    sched[s++] = (pe + i) % (n - 1);

	       i = (which_pe - pe + (n - 1)) % (n - 1);
	       if (i < n/2)
		    sched[s++] = (pe - i + (n - 1)) % (n - 1);
	  }
     }
     A(s == npes);
}
