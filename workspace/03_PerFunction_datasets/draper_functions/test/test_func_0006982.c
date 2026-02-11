vcc_new_expr(void)
{
	struct expr *e;


	ALLOC_OBJ(e, EXPR_MAGIC);
	AN(e);
	e->vsb = VSB_new_auto();
	e->fmt = VOID;
	return (e);
}
