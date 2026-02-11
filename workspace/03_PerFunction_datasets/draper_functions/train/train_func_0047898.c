go_data_matrix_get_value (GODataMatrix *mat, unsigned i, unsigned j)
{
	g_return_val_if_fail (((int)i < mat->size.rows) && ((int)j < mat->size.columns), go_nan);
	if (! (mat->base.flags & GO_DATA_CACHE_IS_VALID)) {
		GODataMatrixClass const *klass = GO_DATA_MATRIX_GET_CLASS (mat);
		g_return_val_if_fail (klass != NULL, go_nan);
		return (*klass->get_value) (mat, i, j);
	}

	return mat->values[i * mat->size.columns + j];
}
