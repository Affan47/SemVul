VCL_Nuke(struct vcls *vcl)
{

	ASSERT_CLI();
	assert(vcl != vcl_active);
	assert(vcl->conf->discard);
	assert(vcl->conf->busy == 0);
	VTAILQ_REMOVE(&vcl_head, vcl, list);
	(void)vcl->conf->fini_func(NULL);
	vcl->conf->fini_vcl(NULL);
	free(vcl->name);
	(void)dlclose(vcl->dlh);
	FREE_OBJ(vcl);
	VSC_C_main->n_vcl--;
	VSC_C_main->n_vcl_discard--;
}
