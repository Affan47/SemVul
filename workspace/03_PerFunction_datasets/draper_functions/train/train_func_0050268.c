canFollowRight(Constraint *c, const Variable* const last) {
	return c->right->block==this && c->active && last!=c->right;
}
