readsf_open(t_readsf *x, t_symbol *s, int argc, t_atom *argv)
{
    t_symbol *filesym = atom_getsymbolarg(0, argc, argv);
    t_float onsetframes = atom_getfloatarg(1, argc, argv);
    t_float headerbytes = atom_getfloatarg(2, argc, argv);
    t_float channels = atom_getfloatarg(3, argc, argv);
    t_float bytespersamp = atom_getfloatarg(4, argc, argv);
    t_symbol *endian = atom_getsymbolarg(5, argc, argv);
    if (!*filesym->s_name)
        return;
    pthread_mutex_lock(&x->x_mutex);
    x->x_requestcode = REQUEST_OPEN;
    x->x_filename = filesym->s_name;
    x->x_fifotail = 0;
    x->x_fifohead = 0;
    if (*endian->s_name == 'b')
         x->x_bigendian = 1;
    else if (*endian->s_name == 'l')
         x->x_bigendian = 0;
    else if (*endian->s_name)
        pd_error(x, "endianness neither 'b' nor 'l'");
    else x->x_bigendian = garray_ambigendian();
    x->x_onsetframes = (onsetframes > 0 ? onsetframes : 0);
    x->x_skipheaderbytes = (headerbytes > 0 ? headerbytes :
        (headerbytes == 0 ? -1 : 0));
    x->x_sfchannels = (channels >= 1 ? channels : 1);
    x->x_bytespersample = (bytespersamp > 2 ? bytespersamp : 2);
    x->x_eof = 0;
    x->x_fileerror = 0;
    x->x_state = STATE_STARTUP;
    sfread_cond_signal(&x->x_requestcondition);
    pthread_mutex_unlock(&x->x_mutex);
}
