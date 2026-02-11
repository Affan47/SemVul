cstate_branch_free(void *that)
{
    cstate_branch_ty *this_thing;

    this_thing = (cstate_branch_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("cstate_branch_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    str_free(this_thing->forced_develop_begin_notify_command);
    str_free(this_thing->develop_end_notify_command);
    str_free(this_thing->develop_end_undo_notify_command);
    str_free(this_thing->review_begin_notify_command);
    str_free(this_thing->review_begin_undo_notify_command);
    str_free(this_thing->review_pass_notify_command);
    str_free(this_thing->review_pass_undo_notify_command);
    str_free(this_thing->review_fail_notify_command);
    str_free(this_thing->integrate_pass_notify_command);
    str_free(this_thing->integrate_fail_notify_command);
    cstate_branch_history_list_free(this_thing->history);
    cstate_branch_change_list_free(this_thing->change);
    cstate_branch_sub_branch_list_free(this_thing->sub_branch);
    cstate_branch_administrator_list_free(this_thing->administrator);
    cstate_branch_developer_list_free(this_thing->developer);
    cstate_branch_reviewer_list_free(this_thing->reviewer);
    cstate_branch_integrator_list_free(this_thing->integrator);
    str_free(this_thing->default_development_directory);
    mem_free(this_thing);
    trace(("}\n"));
}
