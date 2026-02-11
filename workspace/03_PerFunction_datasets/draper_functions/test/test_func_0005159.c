restore_undo (void)
{

    if (f_setup.undo_slots == 0)

	return -1;

    if (curr_undo == NULL)

	return 0;


    memcpy (zmp, prev_zmp, h_dynamic_size);
    SET_PC (curr_undo->pc)
    sp = stack + STACK_SIZE - curr_undo->stack_size;
    fp = stack + curr_undo->frame_offset;
    frame_count = curr_undo->frame_count;
    mem_undiff ((zbyte *) (curr_undo + 1), curr_undo->diff_size, prev_zmp);
    memcpy (sp, (zbyte *)(curr_undo + 1) + curr_undo->diff_size,
	    curr_undo->stack_size * sizeof (*sp));

    curr_undo = curr_undo->prev;

    restart_header ();

    return 2;

}
