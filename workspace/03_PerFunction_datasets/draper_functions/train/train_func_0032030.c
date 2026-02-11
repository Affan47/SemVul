zBNTreeModelFlushCache (zBNTreeModel *model) {
	int i;

	if (model->type == BNTREE_ARRAY ||
		model->type == BNTREE_CDS) {
		for (i=0; i<model->submodels; i++)
			zBNTreeModelFlushCache (&model->submodel[i]);
	}
	else {
		free_all_caches (model->bntree);
	}
}
