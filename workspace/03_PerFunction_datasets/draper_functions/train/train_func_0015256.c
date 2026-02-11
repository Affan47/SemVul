decode_generic_inst (MonoAotModule *module, guint8 *buf, guint8 **endbuf)
{
	int type_argc, i;
	MonoType **type_argv;
	MonoGenericInst *inst;
	guint8 *p = buf;

	type_argc = decode_value (p, &p);
	type_argv = g_new0 (MonoType*, type_argc);

	for (i = 0; i < type_argc; ++i) {
		MonoClass *pclass = decode_klass_ref (module, p, &p);
		if (!pclass) {
			g_free (type_argv);
			return NULL;
		}
		type_argv [i] = &pclass->byval_arg;
	}

	inst = mono_metadata_get_generic_inst (type_argc, type_argv);
	g_free (type_argv);

	*endbuf = p;

	return inst;
}
