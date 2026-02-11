hwrng_register(struct hwrng *rng)
{
	int err = -EINVAL;
	struct hwrng *old_rng, *tmp;

	if (rng->name == NULL ||
	    (rng->data_read == NULL && rng->read == NULL))
		goto out;

	mutex_lock(&rng_mutex);


	err = -ENOMEM;
	if (!rng_buffer) {
		rng_buffer = kmalloc(rng_buffer_size(), GFP_KERNEL);
		if (!rng_buffer)
			goto out_unlock;
	}
	if (!rng_fillbuf) {
		rng_fillbuf = kmalloc(rng_buffer_size(), GFP_KERNEL);
		if (!rng_fillbuf) {
			kfree(rng_buffer);
			goto out_unlock;
		}
	}


	err = -EEXIST;
	list_for_each_entry(tmp, &rng_list, list) {
		if (strcmp(tmp->name, rng->name) == 0)
			goto out_unlock;
	}

	init_completion(&rng->cleanup_done);
	complete(&rng->cleanup_done);

	old_rng = current_rng;
	err = 0;
	if (!old_rng) {
		err = set_current_rng(rng);
		if (err)
			goto out_unlock;
	}
	list_add_tail(&rng->list, &rng_list);

	if (old_rng && !rng->init) {


		add_early_randomness(rng);
	}

out_unlock:
	mutex_unlock(&rng_mutex);
out:
	return err;
}
