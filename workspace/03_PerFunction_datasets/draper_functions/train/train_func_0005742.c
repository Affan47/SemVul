cfq_async_queue_prio(struct cfq_group *cfqg, int ioprio_class, int ioprio)
{
	switch (ioprio_class) {
	case IOPRIO_CLASS_RT:
		return &cfqg->async_cfqq[0][ioprio];
	case IOPRIO_CLASS_NONE:
		ioprio = IOPRIO_NORM;

	case IOPRIO_CLASS_BE:
		return &cfqg->async_cfqq[1][ioprio];
	case IOPRIO_CLASS_IDLE:
		return &cfqg->async_idle_cfqq;
	default:
		BUG();
	}
}
