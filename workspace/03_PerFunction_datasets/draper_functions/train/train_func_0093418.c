_mono_reflection_get_type_from_info (MonoTypeNameParse *info, MonoImage *image, gboolean ignorecase)
{
	gboolean type_resolve = FALSE;
	MonoType *type;
	MonoImage *rootimage = image;

	if (info->assembly.name) {
		MonoAssembly *assembly = mono_assembly_loaded (&info->assembly);
		if (!assembly && image && image->assembly && mono_assembly_names_equal (&info->assembly, &image->assembly->aname))


			assembly = image->assembly;
		if (!assembly) {

			assembly = mono_assembly_load (&info->assembly, image->assembly->basedir, NULL);
			if (!assembly)
				return NULL;
		}
		image = assembly->image;
	} else if (!image) {
		image = mono_defaults.corlib;
	}

	type = mono_reflection_get_type_with_rootimage (rootimage, image, info, ignorecase, &type_resolve);
	if (type == NULL && !info->assembly.name && image != mono_defaults.corlib) {
		image = mono_defaults.corlib;
		type = mono_reflection_get_type_with_rootimage (rootimage, image, info, ignorecase, &type_resolve);
	}

	return type;
}
