slope_n_fetch(register slope_susp_type susp, snd_list_type snd_list)
{
    int cnt = 0;
    int togo;
    int n;
    sample_block_type out;
    register sample_block_values_type out_ptr;

    register sample_block_values_type out_ptr_reg;

    register sample_type prev_reg;
    register double scale_reg;
    register sample_block_values_type input_ptr_reg;
    falloc_sample_block(out, "slope_n_fetch");
    out_ptr = out->samples;
    snd_list->block = out;

    while (cnt < max_sample_block_len) {


	togo = max_sample_block_len - cnt;


	susp_check_term_log_samples(input, input_ptr, input_cnt);
	togo = min(togo, susp->input_cnt);


	if (susp->terminate_cnt != UNKNOWN &&
	    susp->terminate_cnt <= susp->susp.current + cnt + togo) {
	    togo = susp->terminate_cnt - (susp->susp.current + cnt);
	    if (togo == 0) break;
	}


	if (!susp->logically_stopped && susp->susp.log_stop_cnt != UNKNOWN) {
	    int to_stop = susp->susp.log_stop_cnt - (susp->susp.current + cnt);


	    if (to_stop < togo) {
		if (to_stop == 0) {
		    if (cnt) {
			togo = 0;
			break;
		    } else


			susp->logically_stopped = true;
		} else


		    togo = to_stop;
	    }
	}

	n = togo;
	prev_reg = susp->prev;
	scale_reg = susp->scale;
	input_ptr_reg = susp->input_ptr;
	out_ptr_reg = out_ptr;
	if (n) do {
{ register sample_type x = *input_ptr_reg++;
*out_ptr_reg++ = (sample_type) ((x - prev_reg) * scale_reg);
prev_reg = x;};
	} while (--n);

	susp->prev = prev_reg;

	susp->input_ptr += togo;
	out_ptr += togo;
	susp_took(input_cnt, togo);
	cnt += togo;
    }


    if (togo == 0 && cnt == 0) {
	snd_list_terminate(snd_list);
    } else {
	snd_list->block_len = cnt;
	susp->susp.current += cnt;
    }

    if (susp->logically_stopped) {
	snd_list->logically_stopped = true;
    } else if (susp->susp.log_stop_cnt == susp->susp.current) {
	susp->logically_stopped = true;
    }
}
