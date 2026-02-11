c_operands_each (VALUE self)
{
	RbCollection *coll = NULL;
	xmmsv_t *operands_list;
	VALUE tmp;

	tmp = rb_iv_get (self, "collection");
	Data_Get_Struct (tmp, RbCollection, coll);

	operands_list = xmmsv_coll_operands_get (coll->real);

	xmmsv_list_foreach (operands_list, operands_each, NULL);

	return self;
}
