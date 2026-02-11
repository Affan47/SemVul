dlm_posix_lock(dlm_lockspace_t *lockspace, u64 number, struct file *file,
		   int cmd, struct file_lock *fl)
{
	struct dlm_ls *ls;
	struct plock_op *op;
	struct plock_xop *xop;
	int rv;

	ls = dlm_find_lockspace_local(lockspace);
	if (!ls)
		return -EINVAL;

	xop = kzalloc(sizeof(*xop), GFP_NOFS);
	if (!xop) {
		rv = -ENOMEM;
		goto out;
	}

	op = &xop->xop;
	op->info.optype		= DLM_PLOCK_OP_LOCK;
	op->info.pid		= fl->fl_pid;
	op->info.ex		= (fl->fl_type == F_WRLCK);
	op->info.wait		= IS_SETLKW(cmd);
	op->info.fsid		= ls->ls_global_id;
	op->info.number		= number;
	op->info.start		= fl->fl_start;
	op->info.end		= fl->fl_end;
	if (fl->fl_lmops && fl->fl_lmops->lm_grant) {


		op->info.owner	= (__u64) fl->fl_pid;
		xop->callback	= fl->fl_lmops->lm_grant;
		locks_init_lock(&xop->flc);
		locks_copy_lock(&xop->flc, fl);
		xop->fl		= fl;
		xop->file	= file;
	} else {
		op->info.owner	= (__u64)(long) fl->fl_owner;
		xop->callback	= NULL;
	}

	send_op(op);

	if (xop->callback == NULL) {
		rv = wait_event_interruptible(recv_wq, (op->done != 0));
		if (rv == -ERESTARTSYS) {
			log_debug(ls, "dlm_posix_lock: wait killed %llx",
				  (unsigned long long)number);
			spin_lock(&ops_lock);
			list_del(&op->list);
			spin_unlock(&ops_lock);
			kfree(xop);
			do_unlock_close(ls, number, file, fl);
			goto out;
		}
	} else {
		rv = FILE_LOCK_DEFERRED;
		goto out;
	}

	spin_lock(&ops_lock);
	if (!list_empty(&op->list)) {
		log_error(ls, "dlm_posix_lock: op on list %llx",
			  (unsigned long long)number);
		list_del(&op->list);
	}
	spin_unlock(&ops_lock);

	rv = op->info.rv;

	if (!rv) {
		if (locks_lock_file_wait(file, fl) < 0)
			log_error(ls, "dlm_posix_lock: vfs lock error %llx",
				  (unsigned long long)number);
	}

	kfree(xop);
out:
	dlm_put_lockspace(ls);
	return rv;
}
