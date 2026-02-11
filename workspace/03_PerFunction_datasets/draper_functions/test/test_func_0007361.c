delaycv_ns_fetch(register delaycv_susp_type susp, snd_list_type snd_list)
{
    int cnt = 0;
    int togo;
    int n;
    sample_block_type out;
    register sample_block_values_type out_ptr;

    register sample_block_values_type out_ptr_reg;

    register sample_type * delayptr_reg;
    register sample_type * endptr_reg;
    register sample_type feedback_scale_reg = susp->feedback->scale;
    register sample_block_values_type feedback_ptr_reg;
    register sample_block_values_type s_ptr_reg;
    falloc_sample_block(out, "delaycv_ns_fetch");
    out_ptr = out->samples;
    snd_list->block = out;

    while (cnt < max_sample_block_len) {


	togo = max_sample_block_len - cnt;


	susp_check_term_samples(s, s_ptr, s_cnt);
	togo = min(togo, susp->s_cnt);


	susp_check_samples(feedback, feedback_ptr, feedback_cnt);
	togo = min(togo, susp->feedback_cnt);


	if (susp->terminate_cnt != UNKNOWN &&
	    susp->terminate_cnt <= susp->susp.current + cnt + togo) {
	    togo = susp->terminate_cnt - (susp->susp.current + cnt);
	    if (togo == 0) break;
	}

	n = togo;
	delayptr_reg = susp->delayptr;
	endptr_reg = susp->endptr;
	feedback_ptr_reg = susp->feedback_ptr;
	s_ptr_reg = susp->s_ptr;
	out_ptr_reg = out_ptr;
	if (n) do {
*out_ptr_reg++ = *delayptr_reg;
         *delayptr_reg = *delayptr_reg * (feedback_scale_reg * *feedback_ptr_reg++) + *s_ptr_reg++;
         if (++delayptr_reg >= endptr_reg) delayptr_reg = susp->delaybuf;;
	} while (--n);

	susp->delayptr = delayptr_reg;
	susp->endptr = endptr_reg;

	susp->feedback_ptr += togo;

	susp->s_ptr += togo;
	out_ptr += togo;
	susp_took(s_cnt, togo);
	susp_took(feedback_cnt, togo);
	cnt += togo;
    }


    if (togo == 0 && cnt == 0) {
	snd_list_terminate(snd_list);
    } else {
	snd_list->block_len = cnt;
	susp->susp.current += cnt;
    }
}
