ubifs_run_commit(struct ubifs_info *c)
{
	int err = 0;

	spin_lock(&c->cs_lock);
	if (c->cmt_state == COMMIT_BROKEN) {
		err = -EROFS;
		goto out;
	}

	if (c->cmt_state == COMMIT_RUNNING_BACKGROUND)


		c->cmt_state = COMMIT_RUNNING_REQUIRED;

	if (c->cmt_state == COMMIT_RUNNING_REQUIRED) {
		spin_unlock(&c->cs_lock);
		return wait_for_commit(c);
	}
	spin_unlock(&c->cs_lock);


	down_write(&c->commit_sem);
	spin_lock(&c->cs_lock);


	if (c->cmt_state == COMMIT_BROKEN) {
		err = -EROFS;
		goto out_cmt_unlock;
	}

	if (c->cmt_state == COMMIT_RUNNING_BACKGROUND)
		c->cmt_state = COMMIT_RUNNING_REQUIRED;

	if (c->cmt_state == COMMIT_RUNNING_REQUIRED) {
		up_write(&c->commit_sem);
		spin_unlock(&c->cs_lock);
		return wait_for_commit(c);
	}
	c->cmt_state = COMMIT_RUNNING_REQUIRED;
	spin_unlock(&c->cs_lock);

	err = do_commit(c);
	return err;

out_cmt_unlock:
	up_write(&c->commit_sem);
out:
	spin_unlock(&c->cs_lock);
	return err;
}
