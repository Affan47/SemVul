call (zword routine, int argc, zword *args, int ct)
{
    long pc;
    zword value;
    zbyte count;
    int i;

    if (sp - stack < 4)
	runtime_error (ERR_STK_OVF);

    GET_PC (pc)

    *--sp = (zword) (pc >> 9);
    *--sp = (zword) (pc & 0x1ff);
    *--sp = (zword) (fp - stack - 1);
    *--sp = (zword) (argc | (ct << (f_setup.save_quetzal ? 12 : 8)));

    fp = sp;
    frame_count++;


    if (h_version <= V3)
	pc = (long) routine << 1;
    else if (h_version <= V5)
	pc = (long) routine << 2;
    else if (h_version <= V7)
	pc = ((long) routine << 2) + ((long) h_functions_offset << 3);
    else
	pc = (long) routine << 3;

    if (pc >= story_size)
	runtime_error (ERR_ILL_CALL_ADDR);

    SET_PC (pc)


    CODE_BYTE (count)

    if (count > 15)
	runtime_error (ERR_CALL_NON_RTN);
    if (sp - stack < count)
	runtime_error (ERR_STK_OVF);

    if (f_setup.save_quetzal)
	fp[0] |= (zword) count << 8;

    value = 0;

    for (i = 0; i < count; i++) {

	if (h_version <= V4)
	    CODE_WORD (value)

	*--sp = (zword) ((argc-- > 0) ? args[i] : value);

    }


    if (ct == 2)
	interpret ();

}
