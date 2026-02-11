free_task(task * t, int strong)
{

    switch (t->kind) {
    default:
	panic("Unknown task kind in free_task()");
	break;
    case TASK_BINARY:
    case TASK_INBAND:
    case TASK_QUOTED:
    case TASK_OOB:
	free_str(t->t.input.string);
	break;
    case TASK_FORKED:
	if (strong) {
	    free_rt_env(t->t.forked.rt_env,
			t->t.forked.program->num_var_names);
	    free_str(t->t.forked.a.verb);
	    free_str(t->t.forked.a.verbname);
	    free_var(t->t.forked.a.THIS);
	}
	free_program(t->t.forked.program);
	break;
    case TASK_SUSPENDED:
	if (strong)
	    free_vm(t->t.suspended.the_vm, 1);
	break;
    }
    myfree(t, M_TASK);
}
