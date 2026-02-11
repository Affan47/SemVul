cb_get_value (GnmValueIter const *iter, gpointer user_data)
{
	GnmValue *res = user_data;

	value_array_set (res, iter->x, iter->y,
			 iter->v
			 ? value_dup (iter->v)
			 : value_new_int (0));

	return NULL;
}
