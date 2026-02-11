__run (struct synctask *task)
{
        struct syncenv *env = NULL;

        env = task->env;

        list_del_init (&task->all_tasks);
	switch (task->state) {
	case SYNCTASK_INIT:
        case SYNCTASK_SUSPEND:
		break;
	case SYNCTASK_RUN:
		gf_log (task->xl->name, GF_LOG_WARNING,
			"re-running already running task");
		env->runcount--;
		break;
	case SYNCTASK_WAIT:
		env->waitcount--;
		break;
	case SYNCTASK_DONE:
		gf_log (task->xl->name, GF_LOG_WARNING,
			"running completed task");
		break;
	}

        list_add_tail (&task->all_tasks, &env->runq);
	env->runcount++;
	task->state = SYNCTASK_RUN;
}
