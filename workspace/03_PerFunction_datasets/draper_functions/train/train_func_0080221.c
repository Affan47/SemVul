insert_ctrl(seq, ctime, cline, ctrl, voice, value)
  seq_type seq;
  time_type ctime;
  int cline;
  int ctrl;
  int voice;
  int value;
{
    register event_type event = event_create(seq, ctrlsize, ctime, cline);
    if (seq_print) {
        gprintf(TRANS,
            "ctrl(%lx): time %ld, line %d, ctrl %d, voice %d, value %d\n",
            event, ctime, cline, ctrl, voice, value);
    }
    if (event) {
        seq_used_mask(seq) |= 1 << (voice - 1);
        event->nvoice = ctrl_voice(ctrl, voice);
        event->value = value;
        seq_ctrlcount(seq)++;
    }
    return event;
}
