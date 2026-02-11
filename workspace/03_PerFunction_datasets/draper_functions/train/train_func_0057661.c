get_loop_opts (ExecState *s, int *err)
{
    gretlopt opt = OPT_NONE;

    if (compile_level > 0) {

	opt = get_gretl_options(s->line, err);
    } else {
	opt = s->cmd->opt;
    }

    return opt;
}
