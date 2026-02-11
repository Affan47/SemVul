send_macro(ptr, voice, parameter, parm_num, value, nline)
  register unsigned char *ptr;
  int voice;
  short parameter[];
  int parm_num;
  int value;
  int nline;
{
    register unsigned char code, *loc;
    while ((code = *ptr++)) {
        loc = ptr + *ptr;
        ptr++;
        if (code <= nmacroparms) {
            code--;
            *loc = (code == parm_num ? value : parameter[code]) & 0x7f;
        } else if (code == nmacroparms + 1) {

            *loc = (*loc & 0xF0) | ((voice - 1) & 0xF);
        } else {
            code -= (nmacroparms + 2);
            *loc = ((code == parm_num ? value : parameter[code]) >> 7) & 0x7F;
        }
    }
    if (ptr[1] == MIDI_SYSEX) {
        midi_exclusive(ptr + 1);
    } else {


        if (*ptr > 3) {
            gprintf(ERROR,
                    "Non-sysex macro longer than 3 bytes ignored, line %d.\n",
                     nline);
        } else {
            midi_write((int) *ptr, MIDI_PORT(voice), ptr[1], ptr[2], ptr[3]);
        }
    }
}
