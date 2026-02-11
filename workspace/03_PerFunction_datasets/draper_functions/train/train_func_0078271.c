find_tqueue(Objid player, int create_if_not_found)
{
    tqueue *tq;

    for (tq = active_tqueues; tq; tq = tq->next)
	if (tq->player == player)
	    return tq;

    for (tq = idle_tqueues; tq; tq = tq->next)
	if (tq->player == player)
	    return tq;

    if (!create_if_not_found)
	return 0;

    tq = mymalloc(sizeof(tqueue), M_TASK);

    deactivate_tqueue(tq);

    tq->player = player;
    tq->handler = 0;
    tq->connected = 0;

    tq->first_input = tq->first_itail = tq->first_bg = 0;
    tq->last_input = &(tq->first_input);
    tq->last_itail = &(tq->first_itail);
    tq->last_bg = &(tq->first_bg);
    tq->total_input_length = tq->input_suspended = 0;

    tq->output_prefix = tq->output_suffix = 0;
    tq->flush_cmd = default_flush_command();
    tq->program_stream = 0;

    tq->reading = 0;
    tq->hold_input = 0;
    tq->disable_oob = 0;
    tq->icmds = ICMD_ALL_CMDS;
    tq->num_bg_tasks = 0;
    tq->last_input_task_id = 0;

    return tq;
}
