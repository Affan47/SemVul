doview(void)
{
	unsigned  jcnt;

	if  (nwanted != 0)  {
		for  (jcnt = 0;  jcnt < nwanted;  jcnt++)  {
			const  Hashspq *hjp = find_job(&wanted_list[jcnt]);
			if  (hjp)
				check_viewj(&hjp->j);
		}
	}
	else  {
		for  (jcnt = 0;  jcnt < Job_seg.njobs;  jcnt++)  {
			const  struct  spq  *jp = &Job_seg.jj_ptrs[jcnt]->j;
			if  (jp->spq_job == 0)
				continue;
			check_viewj(jp);
		}
	}
}
