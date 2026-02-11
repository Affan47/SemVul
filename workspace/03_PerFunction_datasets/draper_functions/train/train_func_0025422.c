inst_hole(struct obj *obj, struct coord a, struct coord b)
{
	struct inst *inst;

	if (zero_sized(a, b, "%s hole", NULL))
		return 0;
	inst = add_inst(&hole_ops, ip_hole, a);
	inst->obj = obj;
	inst->u.hole.other = b;
	inst->u.hole.layers = mech_hole_layers();
	find_inst(inst);
	update_bbox(&inst->bbox, b);
	propagate_bbox(inst);
	return 1;
}
