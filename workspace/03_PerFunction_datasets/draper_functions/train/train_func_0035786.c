isforever(exp)
register struct nodestruct *exp;
{
    return exp == NULL ||
	(exp->tag == LEAF && exp->left.symptr->storage == CONSTANT &&
	exp->left.symptr->offset.offv != 0);
}
