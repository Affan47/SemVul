camel_index_set_normalize (CamelIndex *index,
                           CamelIndexNorm func,
                           gpointer data)
{
	g_return_if_fail (CAMEL_IS_INDEX (index));

	index->normalize = func;
	index->normalize_data = data;
}
