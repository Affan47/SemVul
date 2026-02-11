insert_call(seq, ctime, cline, voice, addr, value, n)
  seq_type seq;
  time_type ctime;
  int cline;
  int voice;
  int (*addr)();
  long value[SEQ_MAX_PARMS];
  int n;
{
    int i;
    register event_type event = event_create(seq, callsize, ctime, cline);
    if (seq_print) {
        gprintf(TRANS,
            "call(%lx): time %ld, line %d, voice %d, fn %lx,\n\tvalues:",
            event, ctime, cline, voice, addr);
        for (i = 0; i < n; i++) gprintf(TRANS, " %ld", value[i]);
        gprintf(TRANS, "\n");
    }
    if (event) {
        seq_used_mask(seq) |= 1 << (voice - 1);
        event->nvoice = ctrl_voice(ESC_CTRL, voice);
        event->value = CALL_VALUE;
        event->u.call.routine = addr;

        for (i = 0; i < n; i++) event->u.call.args.a[i] = value[i];
        seq_ctrlcount(seq)++;
    }
    return event;
}
