smfw_noteoff(seq_type seq, int voice, int pitch)
{
    if(debug)       gprintf(TRANS, "smfw_noteoff %d: %d (time:%ld)\n", voice, pitch, virttime);
    smfw_deltatime();
    putc(NOTEOFF | (voice - 1), smfw_seq.outfile);
    putc(pitch, smfw_seq.outfile);
    putc(0x40, smfw_seq.outfile);
}
