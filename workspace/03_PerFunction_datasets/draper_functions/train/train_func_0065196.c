subscript_data_attribute (type)
     tree type;
{
  unsigned dimension_number;
  char begin_label[MAX_ARTIFICIAL_LABEL_BYTES];
  char end_label[MAX_ARTIFICIAL_LABEL_BYTES];

  ASM_OUTPUT_DWARF_ATTRIBUTE (asm_out_file, AT_subscr_data);
  sprintf (begin_label, SS_BEGIN_LABEL_FMT, current_dienum);
  sprintf (end_label, SS_END_LABEL_FMT, current_dienum);
  ASM_OUTPUT_DWARF_DELTA2 (asm_out_file, end_label, begin_label);
  ASM_OUTPUT_LABEL (asm_out_file, begin_label);


  for (dimension_number = 0;
	TREE_CODE (type) == ARRAY_TYPE;
	type = TREE_TYPE (type), dimension_number++)
    {
      tree domain = TYPE_DOMAIN (type);


      if (domain)
	{


	  tree lower = TYPE_MIN_VALUE (domain);
	  tree upper = TYPE_MAX_VALUE (domain);


	  if (! type_is_fundamental (domain))
	    abort ();


	  ASM_OUTPUT_DWARF_FMT_BYTE (asm_out_file,
		  FMT_CODE (1, TREE_CODE (lower) == INTEGER_CST,
			    upper && TREE_CODE (upper) == INTEGER_CST));


	  ASM_OUTPUT_DWARF_FUND_TYPE (asm_out_file,
				      fundamental_type_code (domain));


	  output_bound_representation (lower, dimension_number, 'l');


	  if (upper)
	    output_bound_representation (upper, dimension_number, 'u');
	  else
	    ASM_OUTPUT_DWARF_DATA2 (asm_out_file, 0);
	}
      else
	{


	  ASM_OUTPUT_DWARF_FMT_BYTE (asm_out_file, FMT_FT_C_X);


	  ASM_OUTPUT_DWARF_FUND_TYPE (asm_out_file, FT_integer);


	  ASM_OUTPUT_DWARF_DATA4 (asm_out_file, 0);


	  ASM_OUTPUT_DWARF_DATA2 (asm_out_file, 0);
	}
    }


  ASM_OUTPUT_DWARF_FMT_BYTE (asm_out_file, FMT_ET);


  type_attribute (type, 0, 0);

  ASM_OUTPUT_LABEL (asm_out_file, end_label);
}
