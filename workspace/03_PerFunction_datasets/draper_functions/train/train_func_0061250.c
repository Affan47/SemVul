compute_llvm_code_range (MonoAotModule *amodule, guint8 **code_start, guint8 **code_end)
{
	guint8 *p;
	int version, fde_count;
	gint32 *table;

	if (amodule->info.llvm_get_method) {
		gpointer (*get_method) (int) = (gpointer (*)(int))amodule->info.llvm_get_method;

		*code_start = (guint8 *)get_method (-1);
		*code_end = (guint8 *)get_method (-2);

		g_assert (*code_end > *code_start);
		return;
	}

	g_assert (amodule->mono_eh_frame);

	p = amodule->mono_eh_frame;


	version = *p;
	g_assert (version == 3);
	p ++;
	p ++;
	p = (guint8 *)ALIGN_PTR_TO (p, 4);

	fde_count = *(guint32*)p;
	p += 4;
	table = (gint32*)p;

	if (fde_count > 0) {
		*code_start = (guint8 *)amodule->methods [table [0]];
		*code_end = (guint8*)amodule->methods [table [(fde_count - 1) * 2]] + table [fde_count * 2];
	} else {
		*code_start = NULL;
		*code_end = NULL;
	}
}
