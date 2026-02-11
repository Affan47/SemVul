inst_get_vec(const struct inst *inst)
{
	if (inst->ops == &vec_ops)
		return inst->vec;
	if (inst->ops == &frame_ops)
		return NULL;
	abort();
}
