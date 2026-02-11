cstate_branch_clone(cstate_branch_ty *this_thing)
{
    if (!this_thing)
	return 0;
    trace(("cstate_branch_clone()\n{\n"));
    cstate_branch_ty *result = (cstate_branch_ty *)cstate_branch_alloc();
    result->umask = this_thing->umask;
    result->developer_may_review = this_thing->developer_may_review;
    result->developer_may_integrate = this_thing->developer_may_integrate;
    result->reviewer_may_integrate = this_thing->reviewer_may_integrate;
    result->developers_may_create_changes = this_thing->developers_may_create_changes;
    result->forced_develop_begin_notify_command = str_copy(this_thing->forced_develop_begin_notify_command);
    result->develop_end_notify_command = str_copy(this_thing->develop_end_notify_command);
    result->develop_end_undo_notify_command = str_copy(this_thing->develop_end_undo_notify_command);
    result->review_begin_notify_command = str_copy(this_thing->review_begin_notify_command);
    result->review_begin_undo_notify_command = str_copy(this_thing->review_begin_undo_notify_command);
    result->review_pass_notify_command = str_copy(this_thing->review_pass_notify_command);
    result->review_pass_undo_notify_command = str_copy(this_thing->review_pass_undo_notify_command);
    result->review_fail_notify_command = str_copy(this_thing->review_fail_notify_command);
    result->integrate_pass_notify_command = str_copy(this_thing->integrate_pass_notify_command);
    result->integrate_fail_notify_command = str_copy(this_thing->integrate_fail_notify_command);
    result->default_test_exemption = this_thing->default_test_exemption;
    result->default_test_regression_exemption = this_thing->default_test_regression_exemption;
    result->skip_unlucky = this_thing->skip_unlucky;
    result->compress_database = this_thing->compress_database;
    result->develop_end_action = this_thing->develop_end_action;
    result->history = cstate_branch_history_list_clone(this_thing->history);
    result->change = cstate_branch_change_list_clone(this_thing->change);
    result->sub_branch = cstate_branch_sub_branch_list_clone(this_thing->sub_branch);
    result->administrator = cstate_branch_administrator_list_clone(this_thing->administrator);
    result->developer = cstate_branch_developer_list_clone(this_thing->developer);
    result->reviewer = cstate_branch_reviewer_list_clone(this_thing->reviewer);
    result->integrator = cstate_branch_integrator_list_clone(this_thing->integrator);
    result->currently_integrating_change = this_thing->currently_integrating_change;
    result->default_development_directory = str_copy(this_thing->default_development_directory);
    result->minimum_change_number = this_thing->minimum_change_number;
    result->reuse_change_numbers = this_thing->reuse_change_numbers;
    result->minimum_branch_number = this_thing->minimum_branch_number;
    result->protect_development_directory = this_thing->protect_development_directory;
    trace(("return %08lX;\n", (long)result));
    trace(("}\n"));
    return result;
}
