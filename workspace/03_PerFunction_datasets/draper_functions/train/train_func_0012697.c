adjust_alleles()
{
  int pedidx, locidx, old_all, new_all;
  int missed;

  locusvalues **templocus;

   templocus = thislocus;

    pedidx = currentped;
    for(locidx = 0; locidx < nsystem; locidx++)
      if ((binary_ == templocus[locidx]->which) &&
           (allformat == templocus[locidx]->UU.U2.format)) {

        old_all = 1;
        new_all = 1;
        missed = 0;
        while (old_all <= templocus[locidx]->maxallele) {
          if (ped_loc_all[pedidx][locidx][old_all].present) {
             ped_loc_all[pedidx][locidx][old_all].new_allele = new_all;
             ped_loc_all[pedidx][locidx][new_all].old_allele = old_all;
             new_all++;
	  }
          else
            missed = old_all;
          old_all++;
	}


        if (new_all < old_all) {
          ped_loc_all[pedidx][locidx][new_all].old_allele = missed;
          new_all++;
	}
        ped_new_allele_count[pedidx][locidx] = new_all - 1;
      }
}
