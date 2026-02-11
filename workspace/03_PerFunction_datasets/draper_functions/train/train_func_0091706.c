seq_play(seq)
  seq_type seq;
{
    timebase_type prev_timebase = timebase;
    register timebase_type reg_timebase = seq->timebase;

    if (!seq->runflag) {
        seq_reset(seq);
    }
    if (!seq->paused) return;
    eventtime = gettime();


    timebase = reg_timebase;
    virttime = reg_timebase->virt_base;

    set_rate(reg_timebase, seq->rate);
    seq->paused = FALSE;

    seq->runflag = TRUE;
    seq->note_enable = TRUE;


    timebase_use(prev_timebase);
}
