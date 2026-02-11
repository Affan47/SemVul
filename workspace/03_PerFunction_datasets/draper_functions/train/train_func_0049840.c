midgard_core_auth_type_free (MgdCoreAuthType *mcat)
{
	g_assert (mcat != NULL);

	g_free (mcat->name);
	mcat->name = NULL;
	mcat->id = 0;

	g_free (mcat);
	mcat = NULL;
}
