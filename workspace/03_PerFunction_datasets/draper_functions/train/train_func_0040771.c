pconf_free(void *that)
{
    pconf_ty	    *this_thing;

    this_thing = (pconf_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("pconf_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    str_free(this_thing->configuration_directory);
    str_free(this_thing->build_command);
    work_area_style_free(this_thing->integration_directory_style);
    work_area_style_free(this_thing->development_directory_style);
    str_free(this_thing->development_build_command);
    str_free(this_thing->build_time_adjust_notify_command);
    str_free(this_thing->change_file_command);
    str_free(this_thing->new_file_command);
    str_free(this_thing->new_test_command);
    str_free(this_thing->copy_file_command);
    str_free(this_thing->remove_file_command);
    str_free(this_thing->change_file_undo_command);
    str_free(this_thing->new_file_undo_command);
    str_free(this_thing->new_test_undo_command);
    str_free(this_thing->copy_file_undo_command);
    str_free(this_thing->remove_file_undo_command);
    str_free(this_thing->make_transparent_command);
    str_free(this_thing->make_transparent_undo_command);
    str_free(this_thing->project_file_command);
    str_free(this_thing->develop_begin_command);
    str_free(this_thing->develop_begin_undo_command);
    str_free(this_thing->integrate_begin_command);
    str_free(this_thing->integrate_begin_undo_command);
    pconf_integrate_begin_exceptions_list_free(this_thing->integrate_begin_exceptions);
    pconf_symlink_exceptions_list_free(this_thing->symlink_exceptions);
    str_free(this_thing->history_create_command);
    str_free(this_thing->history_get_command);
    str_free(this_thing->history_put_command);
    str_free(this_thing->history_query_command);
    str_free(this_thing->history_transaction_begin_command);
    str_free(this_thing->history_transaction_end_command);
    str_free(this_thing->history_transaction_abort_command);
    str_free(this_thing->history_label_command);
    str_free(this_thing->diff_command);
    str_free(this_thing->diff3_command);
    str_free(this_thing->merge_command);
    str_free(this_thing->patch_diff_command);
    str_free(this_thing->annotate_diff_command);
    str_free(this_thing->test_command);
    str_free(this_thing->development_test_command);
    str_free(this_thing->batch_test_command);
    str_free(this_thing->architecture_discriminator_command);
    pconf_architecture_list_free(this_thing->architecture);
    pconf_file_template_list_free(this_thing->file_template);
    pconf_whiteout_template_list_free(this_thing->whiteout_template);
    pconf_filename_pattern_accept_list_free(this_thing->filename_pattern_accept);
    pconf_filename_pattern_reject_list_free(this_thing->filename_pattern_reject);
    str_free(this_thing->new_test_filename);
    str_free(this_thing->development_directory_template);
    str_free(this_thing->metrics_filename_pattern);
    pconf_trojan_horse_suspect_list_free(this_thing->trojan_horse_suspect);
    attributes_list_type.free(this_thing->project_specific);
    str_free(this_thing->review_policy_command);
    str_free(this_thing->develop_end_policy_command);
    pconf_clean_exceptions_list_free(this_thing->clean_exceptions);
    mem_free(this_thing);
    trace(("}\n"));
}
