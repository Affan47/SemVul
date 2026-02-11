dependent_pos (GnmDependent const *dep)
{
	static GnmCellPos const dummy = { 0, 0 };
	int const t = dependent_type (dep);
	GnmDependentClass *klass = g_ptr_array_index (dep_classes, t);

	return klass->pos ? klass->pos (dep) : &dummy;
}
