sound_xlmark(s)
sound_type s;
{
    snd_list_type snd_list;
    long counter = 0;
#ifdef TRACESNDGC
    nyquist_printf("sound_xlmark(%p)\n", s);
#endif
    if (!s) return;
    snd_list = s->list;
    while (snd_list->block != NULL) {
        if (snd_list == zero_snd_list) {
#ifdef TRACESNDGC
            stdputstr(" terminates at zero_snd_list\n");
#endif
            return;
        } else if (counter > 1000000) {
            stdputstr("You created a recursive sound! This is a Nyquist bug.\n");
            stdputstr("The only known way to do this is by a SETF on a\n");
            stdputstr("local variable or parameter that is being passed to SEQ\n");
            stdputstr("or SEQREP. The garbage collector assumes that sounds are\n");
            stdputstr("not recursive or circular, and follows sounds to their\n");
            stdputstr("end. After following a million nodes, I'm pretty sure\n");
            stdputstr("that there is a cycle here, but since this is a bug,\n");
            stdputstr("I cannot promise to recover. Prepare to crash. If you\n");
            stdputstr("cannot locate the cause of this, contact the author -RBD.\n");
        }
        snd_list = snd_list->u.next;
        counter++;
    }
    if (snd_list->u.susp->mark) {
#ifdef TRACESNDGC
        nyquist_printf(" found susp (%s) at %p with mark method\n",
               snd_list->u.susp->name, snd_list->u.susp);
#endif
        (*(snd_list->u.susp->mark))(snd_list->u.susp);
    } else {
#ifdef TRACESNDGC
        nyquist_printf(" no mark method on susp %p (%s)\n",
               snd_list->u.susp, snd_list->u.susp->name);
#endif
    }
}
