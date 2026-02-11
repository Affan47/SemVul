avg_toss_fetch(susp, snd_list)
  avg_susp_type susp;
  snd_list_type snd_list;
{
    long final_count = MIN(susp->susp.current + max_sample_block_len,
               susp->susp.toss_cnt);
    time_type final_time = susp->susp.t0 + final_count / susp->susp.sr;
    long n;


    while (((long) ((final_time - susp->s->t0) * susp->s->sr + 0.5)) >=
       susp->s->current)
    susp_get_samples(s, s_ptr, s_cnt);


    if (final_count == susp->susp.toss_cnt) {
    n = ROUND((final_time - susp->s->t0) * susp->s->sr -
         (susp->s->current - susp->s_cnt));
    susp->s_ptr += n;
    susp_took(s_cnt, n);
    susp->susp.fetch = susp->susp.keep_fetch;
    }
    snd_list->block_len = (short) (final_count - susp->susp.current);
    susp->susp.current = final_count;
    snd_list->u.next = snd_list_create((snd_susp_type) susp);
    snd_list->block = internal_zero_block;
}
