svm_free_model_content(svm_model* model_ptr)
{
	if(model_ptr->free_sv && model_ptr->l > 0)
		free((void *)(model_ptr->SV[0]));
	for(int i=0;i<model_ptr->nr_class-1;i++)
		free(model_ptr->sv_coef[i]);
	free(model_ptr->SV);
	free(model_ptr->sv_coef);
	free(model_ptr->rho);
	free(model_ptr->label);
	free(model_ptr->probA);
	free(model_ptr->probB);
	free(model_ptr->nSV);
}
