mono_jit_info_get_thunk_info (MonoJitInfo *ji)
{
	if (ji->has_thunk_info) {
		char *ptr = (char*)&ji->clauses [ji->num_clauses];
		if (ji->has_generic_jit_info)
			ptr += sizeof (MonoGenericJitInfo);
		if (ji->has_try_block_holes)
			ptr += try_block_hole_table_size (ji);
		if (ji->has_arch_eh_info)
			ptr += sizeof (MonoArchEHJitInfo);
		return (MonoThunkJitInfo*)ptr;
	} else {
		return NULL;
	}
}
