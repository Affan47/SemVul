harminv_solve_ok_modes(harminv_data d, harminv_mode_ok_func ok,void *ok_d)
{

     harminv_solve_once(d);


     {
	  int prev_nf, cur_nf, nf_ok;
	  cur_nf = harminv_get_num_freqs(d);
	  do {
	       prev_nf = cur_nf;
	       harminv_solve_again(d, ok, ok_d);
	       cur_nf = harminv_get_num_freqs(d);
	       if (ok) {
		    ok(d, -1, ok_d);
		    for (nf_ok = 0; nf_ok < cur_nf
			      && ok(d, nf_ok, ok_d); ++nf_ok)
			 ;
		    ok(d, -2, ok_d);
	       }
	       else
		    nf_ok = cur_nf;
	  } while (cur_nf < prev_nf || nf_ok < cur_nf);

     }
}
