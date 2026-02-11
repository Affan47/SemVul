add_inst(const struct inst_ops *ops, enum inst_prio prio,
    struct coord base)
{
	struct inst *inst;

	inst = alloc_type(struct inst);
	inst->ops = ops;
	inst->prio = prio;
	inst->vec = NULL;
	inst->obj = NULL;
	inst->base = inst->bbox.min = inst->bbox.max = base;
	inst->outer = frame_instantiating;
	inst->active = IS_ACTIVE;
	inst->next = NULL;
	*curr_pkg->next_inst[prio] = inst;
	curr_pkg->next_inst[prio] = &inst->next;
	return inst;
}
