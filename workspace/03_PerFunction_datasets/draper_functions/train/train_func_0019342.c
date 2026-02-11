vte_init(void)
{
	if (vte_info.have_vte == FALSE)
	{
		geany_debug("Disabling terminal support");
		return;
	}

	if (NZV(vte_info.lib_vte))
	{
		module = g_module_open(vte_info.lib_vte, G_MODULE_BIND_LAZY);
	}
#ifdef VTE_MODULE_PATH
	else
	{
		module = g_module_open(VTE_MODULE_PATH, G_MODULE_BIND_LAZY);
	}
#endif

	if (module == NULL)
	{
		gint i;
		const gchar *sonames[] = {  "libvte.so", "libvte.so.4",
									"libvte.so.8", "libvte.so.9", NULL };

		for (i = 0; sonames[i] != NULL && module == NULL; i++)
		{
			module = g_module_open(sonames[i], G_MODULE_BIND_LAZY);
		}
	}

	if (module == NULL)
	{
		vte_info.have_vte = FALSE;
		geany_debug("Could not load libvte.so, embedded terminal support disabled");
		return;
	}
	else
	{
		vf = g_new0(struct VteFunctions, 1);
		if (vte_register_symbols(module))
			vte_info.have_vte = TRUE;
		else
		{
			vte_info.have_vte = FALSE;
			g_free(vf);


			module = NULL;
			return;
		}
	}

	create_vte();


	override_menu_key();
}
