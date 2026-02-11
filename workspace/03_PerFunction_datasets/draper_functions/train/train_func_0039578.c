setup_activ_for_eval(Program * prog)
{
    Var *env;
    if (!push_activation())
	return 0;

    RUN_ACTIV.prog = prog;

    RUN_ACTIV.rt_env = env = new_rt_env(prog->num_var_names);
    fill_in_rt_consts(env, prog->version);
    set_rt_env_obj(env, SLOT_PLAYER, CALLER_ACTIV.player);
    set_rt_env_var(env, SLOT_CALLER, var_ref(CALLER_ACTIV.this));
    set_rt_env_obj(env, SLOT_THIS, NOTHING);
    set_rt_env_obj(env, SLOT_DOBJ, NOTHING);
    set_rt_env_obj(env, SLOT_IOBJ, NOTHING);
    set_rt_env_str(env, SLOT_DOBJSTR, str_dup(""));
    set_rt_env_str(env, SLOT_IOBJSTR, str_dup(""));
    set_rt_env_str(env, SLOT_ARGSTR, str_dup(""));
    set_rt_env_str(env, SLOT_PREPSTR, str_dup(""));
    set_rt_env_str(env, SLOT_VERB, str_dup(""));
    set_rt_env_var(env, SLOT_ARGS, new_list(0));

    RUN_ACTIV.this = var_ref(nothing);
    RUN_ACTIV.player = CALLER_ACTIV.player;
    RUN_ACTIV.progr = CALLER_ACTIV.progr;
    RUN_ACTIV.recv = NOTHING;
    RUN_ACTIV.vloc = NOTHING;
    RUN_ACTIV.verb = str_dup("");
    RUN_ACTIV.verbname = str_dup("Input to EVAL");
    RUN_ACTIV.debug = 1;
    alloc_rt_stack(&RUN_ACTIV, RUN_ACTIV.prog->main_vector.max_stack);
    RUN_ACTIV.pc = 0;
    RUN_ACTIV.error_pc = 0;
    RUN_ACTIV.temp.type = TYPE_NONE;

    return 1;
}
