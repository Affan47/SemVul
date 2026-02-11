coverage_add_class (CoverageClass *klass)
{
	GPtrArray *classes = NULL;

	if (coverage_classes == NULL) {
		coverage_classes = g_ptr_array_new ();
		coverage_assembly_classes = g_hash_table_new (g_str_hash, g_str_equal);
	}

	g_ptr_array_add (coverage_classes, klass);
	classes = (GPtrArray *)g_hash_table_lookup (coverage_assembly_classes, klass->assembly_name);
	if (classes == NULL) {
		classes = g_ptr_array_new ();
		g_hash_table_insert (coverage_assembly_classes, klass->assembly_name, classes);
	}
	g_ptr_array_add (classes, klass);
}
