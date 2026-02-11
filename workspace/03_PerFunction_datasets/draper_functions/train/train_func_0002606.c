refine_overlapping(struct inst *copper, struct inst *other)
{
	if (other->u.pad.layers & LAYER_PASTE_TOP) {
		copper->u.pad.layers &= ~LAYER_PASTE_TOP;
		if (!inside(other, copper)) {
			fail("solder paste without copper underneath "
			    "(\"%s\" line %d, \"%s\" line %d)",
			    copper->u.pad.name, copper->obj->lineno,
			    other->u.pad.name, other->obj->lineno);
			instantiation_error = other->obj;
			return 0;
		}
	}
	if (other->u.pad.layers & LAYER_MASK_TOP)
		copper->u.pad.layers &= ~LAYER_MASK_TOP;
	return 1;
}
