insert_macctrl(seq, ctime, cline, ctrl, voice, value)
  seq_type seq;
  time_type ctime;
  int cline;
  int ctrl;
  int voice;
  int value;
{
    register event_type event = event_create(seq, macctrlsize, ctime, cline);
    if (seq_print) {
        gprintf(TRANS,
            "macctrl(%lx): time %ld, line %d, ctrl %d, voice %d, value %d\n",
            event, ctime, cline, ctrl, voice, value);
    }
    if (event) {
        seq_used_mask(seq) |= 1 << (voice - 1);
        event->nvoice = ctrl_voice(ESC_CTRL, voice);
        event->value = MACCTRL_VALUE;
        event->u.macctrl.ctrl_number = ctrl;
        event->u.macctrl.value = value;
        seq_ctrlcount(seq)++;
    }
    return event;
}
