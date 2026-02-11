smfw_ctrl(seq_type seq, int voice, int ctrl_name, int value)
{
    if(debug)   gprintf(TRANS, "smfw_ctrl %d: %d\n", ctrl_name, value);
    smfw_deltatime();
    putc(MIDI_CTRL | (voice - 1), smfw_seq.outfile);
    putc(ctrl_name, smfw_seq.outfile);
    putc(value, smfw_seq.outfile);
}
