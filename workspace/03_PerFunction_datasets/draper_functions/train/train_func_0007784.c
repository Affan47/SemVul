echainiv_aead_create(struct crypto_template *tmpl,
				struct rtattr **tb)
{
	struct aead_instance *inst;
	struct crypto_aead_spawn *spawn;
	struct aead_alg *alg;
	int err;

	inst = aead_geniv_alloc(tmpl, tb, 0, 0);

	if (IS_ERR(inst))
		return PTR_ERR(inst);

	spawn = aead_instance_ctx(inst);
	alg = crypto_spawn_aead_alg(spawn);

	err = -EINVAL;
	if (inst->alg.ivsize & (sizeof(u64) - 1) || !inst->alg.ivsize)
		goto free_inst;

	inst->alg.encrypt = echainiv_encrypt;
	inst->alg.decrypt = echainiv_decrypt;

	inst->alg.init = aead_init_geniv;
	inst->alg.exit = aead_exit_geniv;

	inst->alg.base.cra_ctxsize = sizeof(struct aead_geniv_ctx);
	inst->alg.base.cra_ctxsize += inst->alg.ivsize;

	inst->free = aead_geniv_free;

	err = aead_register_instance(tmpl, inst);
	if (err)
		goto free_inst;

out:
	return err;

free_inst:
	aead_geniv_free(inst);
	goto out;
}
