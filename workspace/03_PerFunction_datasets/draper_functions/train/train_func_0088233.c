mono_emit_vector_ldelema (MonoCompile *cfg, MonoType *array_type, MonoInst *arr, MonoInst *index, gboolean check_bounds)
{
	MonoInst *ins;
	guint32 size;
	int mult_reg, add_reg, array_reg, index_reg, index2_reg, index3_reg;

	size = mono_array_element_size (mono_class_from_mono_type (array_type));
	mult_reg = alloc_preg (cfg);
	array_reg = arr->dreg;
	index_reg = index->dreg;

#if SIZEOF_VOID_P == 8

	index2_reg = alloc_preg (cfg);
	MONO_EMIT_NEW_UNALU (cfg, OP_SEXT_I4, index2_reg, index_reg);
#else
	index2_reg = index_reg;
#endif
	index3_reg = alloc_preg (cfg);

	if (check_bounds) {
		MONO_EMIT_BOUNDS_CHECK (cfg, array_reg, MonoArray, max_length, index2_reg);
		MONO_EMIT_NEW_BIALU_IMM (cfg,  OP_PADD_IMM, index3_reg, index2_reg, 16 / size - 1);
		MONO_EMIT_BOUNDS_CHECK (cfg, array_reg, MonoArray, max_length, index3_reg);
	}

	add_reg = alloc_preg (cfg);

	MONO_EMIT_NEW_BIALU_IMM (cfg, OP_MUL_IMM, mult_reg, index2_reg, size);
	MONO_EMIT_NEW_BIALU (cfg, OP_PADD, add_reg, array_reg, mult_reg);
	NEW_BIALU_IMM (cfg, ins, OP_PADD_IMM, add_reg, add_reg, MONO_STRUCT_OFFSET (MonoArray, vector));
	ins->type = STACK_PTR;
	MONO_ADD_INS (cfg->cbb, ins);

	return add_reg;
}
