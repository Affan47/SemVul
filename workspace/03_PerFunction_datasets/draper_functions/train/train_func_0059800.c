FsmEvent(struct FsmInst *fi, int event, void *arg)
{
	FSMFNPTR r;

	if ((fi->state >= fi->fsm->state_count) || (event >= fi->fsm->event_count)) {
		printk(KERN_ERR "FsmEvent Error st(%ld/%ld) ev(%d/%ld)\n",
		       (long)fi->state, (long)fi->fsm->state_count, event, (long)fi->fsm->event_count);
		return (1);
	}
	r = fi->fsm->jumpmatrix[fi->fsm->state_count * event + fi->state];
	if (r) {
		if (fi->debug)
			fi->printdebug(fi, "State %s Event %s",
				       fi->fsm->strState[fi->state],
				       fi->fsm->strEvent[event]);
		r(fi, event, arg);
		return (0);
	} else {
		if (fi->debug)
			fi->printdebug(fi, "State %s Event %s no routine",
				       fi->fsm->strState[fi->state],
				       fi->fsm->strEvent[event]);
		return (!0);
	}
}
