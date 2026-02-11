list_content_eval (GnmDependent *dep)
{
	SheetWidgetListBase *swl = DEP_TO_LIST_BASE_CONTENT (dep);
	GnmEvalPos ep;
	GnmValue *v = NULL;
	GtkListStore *model;

	if (dep->texpr != NULL) {
		v = gnm_expr_top_eval (dep->texpr,
				       eval_pos_init_dep (&ep, dep),
				       GNM_EXPR_EVAL_PERMIT_NON_SCALAR |
				       GNM_EXPR_EVAL_PERMIT_EMPTY);
	}
	model = gtk_list_store_new (1, G_TYPE_STRING);
	if (v) {
		value_area_foreach (v, &ep, CELL_ITER_ALL,
				    (GnmValueIterFunc) cb_collect, model);
		value_release (v);
	}

	if (NULL != swl->model)
		g_object_unref (swl->model);
	swl->model = GTK_TREE_MODEL (model);
	g_signal_emit (G_OBJECT (swl), list_base_signals [LIST_BASE_MODEL_CHANGED], 0);
}
