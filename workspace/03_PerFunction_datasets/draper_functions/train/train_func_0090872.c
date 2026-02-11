arm_file_start (void)
{
  int val;

  if (TARGET_UNIFIED_ASM)
    asm_fprintf (asm_out_file, "\t.syntax unified\n");

  if (TARGET_BPABI)
    {
      const char *fpu_name;
      if (arm_selected_arch)
	asm_fprintf (asm_out_file, "\t.arch %s\n", arm_selected_arch->name);
      else if (strncmp (arm_selected_cpu->name, "generic", 7) == 0)
	asm_fprintf (asm_out_file, "\t.arch %s\n", arm_selected_cpu->name + 8);
      else
	asm_fprintf (asm_out_file, "\t.cpu %s\n", arm_selected_cpu->name);

      if (TARGET_SOFT_FLOAT)
	{
	  if (TARGET_VFP)
	    fpu_name = "softvfp";
	  else
	    fpu_name = "softfpa";
	}
      else
	{
	  fpu_name = arm_fpu_desc->name;
	  if (arm_fpu_desc->model == ARM_FP_MODEL_VFP)
	    {
	      if (TARGET_HARD_FLOAT)
		EMIT_EABI_ATTRIBUTE (Tag_ABI_HardFP_use, 27, 3);
	      if (TARGET_HARD_FLOAT_ABI)
		EMIT_EABI_ATTRIBUTE (Tag_ABI_VFP_args, 28, 1);
	    }
	}
      asm_fprintf (asm_out_file, "\t.fpu %s\n", fpu_name);


      if (flag_rounding_math)
	EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_rounding, 19, 1);

      if (!flag_unsafe_math_optimizations)
	{
	  EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_denormal, 20, 1);
	  EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_exceptions, 21, 1);
	}
      if (flag_signaling_nans)
	EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_user_exceptions, 22, 1);

      EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_number_model, 23,
			   flag_finite_math_only ? 1 : 3);

      EMIT_EABI_ATTRIBUTE (Tag_ABI_align8_needed, 24, 1);
      EMIT_EABI_ATTRIBUTE (Tag_ABI_align8_preserved, 25, 1);
      EMIT_EABI_ATTRIBUTE (Tag_ABI_enum_size, 26, flag_short_enums ? 1 : 2);


      if (optimize_size)
	val = 4;
      else if (optimize >= 2)
	val = 2;
      else if (optimize)
	val = 1;
      else
	val = 6;
      EMIT_EABI_ATTRIBUTE (Tag_ABI_optimization_goals, 30, val);

      EMIT_EABI_ATTRIBUTE (Tag_CPU_unaligned_access, 34, unaligned_access);

      if (arm_fp16_format)
	EMIT_EABI_ATTRIBUTE (Tag_ABI_FP_16bit_format, 38, (int) arm_fp16_format);

      if (arm_lang_output_object_attributes_hook)
	arm_lang_output_object_attributes_hook();
    }

  default_file_start ();
}
