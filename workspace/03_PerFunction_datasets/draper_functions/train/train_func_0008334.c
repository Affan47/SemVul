create_command_line_args (CutPipeline *pipeline)
{
    CutRunContext *run_context;
    const gchar **original_argv;
    gchar **new_args = NULL;

    run_context = CUT_RUN_CONTEXT(pipeline);
    g_return_val_if_fail(cut_run_context_get_test_directory(run_context) != NULL,
                         NULL);

    original_argv = cut_run_context_get_command_line_args(run_context);

    if (original_argv) {
        new_args = create_command_line_args_from_argv(pipeline, original_argv);
    } else {
        new_args = create_command_line_args_from_parameters(pipeline);
    }

    return new_args;
}
