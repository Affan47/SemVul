openGPRState(gpr_info* info)
{
    Gpr_t *state;

    if (!(state = newof(0, Gpr_t, 1, 0))) {
	error(ERROR_ERROR, "Could not create gvpr state: out of memory");
	return state;
    }

    if (!(state->tmp = sfstropen())) {
	error(ERROR_ERROR, "Could not create state tmpfile");
	free (state);
	return 0;
    }

    state->tvt = TV_flat;
    state->name_used = name_used;
    state->tvroot = 0;
    state->tvnext = 0;
    state->tvedge = 0;
    state->outFile = info->outFile;
    state->argc = info->argc;
    state->argv = info->argv;
    state->errf = info->errf;
    state->flags = info->flags;

    return state;
}
