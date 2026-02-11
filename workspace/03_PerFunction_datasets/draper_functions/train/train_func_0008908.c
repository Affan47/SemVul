change_history_timestamp_to_delta(project_ty *pp, time_t when)
{
    trace(("%s\n{\n", __PRETTY_FUNCTION__));
    cstate_ty       *cstate_data;
    cstate_branch_history_list_ty *hl;
    change::pointer cp;

    cp = pp->change_get();
    cstate_data = cp->cstate_get();
    if (!cstate_data->branch)
	return 0;
    hl = cstate_data->branch->history;
    if (!hl)
	return 0;

    if (hl->length == 0)
        return 0;

    assert(hl->list);
    if (!hl->list)
        return 0;


    long start = 0;
    long end = hl->length - 1;

    cstate_branch_history_ty *bh_start = hl->list[start];
    assert(bh_start);
    time_t time_start =
        pp->change_completion_timestamp(bh_start->change_number);

    cstate_branch_history_ty *bh_end = hl->list[end];
    assert(bh_end);
    time_t time_end =
        pp->change_completion_timestamp(bh_end->change_number);


    long result = 0;
    for(;;)
    {
        assert (start <= end);

        trace_long(start);
        trace_long(end);

        if (when == time_end)
        {
            assert(hl->list[end]);
            result = hl->list[end]->delta_number;
            break;
        }


        if (when > time_end)
        {
            assert(hl->list[end]);
            result = hl->list[end]->delta_number;
            break;
        }

        if (when == time_start)
        {
            assert(hl->list[start]);
            result = hl->list[start]->delta_number;
            break;
        }


        if (when < time_start)
        {
            result = 0;
            break;
        }


        if (end - start == 1)
        {
            assert (time_end > when);
            assert (when > time_start);
            assert(hl->list[start]);

            result = hl->list[start]->delta_number;
            break;
        }

        long middle = start + (end - start) / 2;

        cstate_branch_history_ty *bh_middle = hl->list[middle];
        assert(bh_middle);
	time_t time_middle =
            pp->change_completion_timestamp(bh_middle->change_number);

        if (when < time_middle)
        {
            time_end = time_middle;
            end = middle;
        }
        else
        {
            time_start = time_middle;
            start = middle;
        }
    }

    return result;
}
