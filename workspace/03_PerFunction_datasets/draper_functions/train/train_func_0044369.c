execute_end(const char *old_command, int truth, String *args)
{
    int error = 0;

    if (pending_line && !read_depth) {
	current_command = NULL;
        error += !handle_input_line();
    }
    current_command = old_command;
    if (!truth) {
        truth = !valbool(user_result);
        set_user_result(newint(truth));
    }
    Stringfree(args);
    return !error;
}
