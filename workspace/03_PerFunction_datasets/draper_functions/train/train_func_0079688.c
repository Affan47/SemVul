mcf_config_show(struct cli *cli, const char * const *av, void *priv)
{
	struct vclprog *vp;
	void *dlh, *sym;
	const char **src;

	(void)priv;
	if ((vp = mcf_find_vcl(cli, av[2])) != NULL) {
		if ((dlh = dlopen(vp->fname, RTLD_NOW | RTLD_LOCAL)) == NULL) {
			VCLI_Out(cli, "failed to load %s: %s\n",
			    vp->name, dlerror());
			VCLI_SetResult(cli, CLIS_CANT);
		} else if ((sym = dlsym(dlh, "srcbody")) == NULL) {
			VCLI_Out(cli, "failed to locate source for %s: %s\n",
			    vp->name, dlerror());
			VCLI_SetResult(cli, CLIS_CANT);
			AZ(dlclose(dlh));
		} else {
			src = sym;
			VCLI_Out(cli, "%s", src[0]);

			AZ(dlclose(dlh));
		}
	}
}
