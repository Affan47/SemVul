add_bound_info (subrange_die, bound_attr, bound)
     dw_die_ref subrange_die;
     enum dwarf_attribute bound_attr;
     tree bound;
{
  switch (TREE_CODE (bound))
    {
    case ERROR_MARK:
      return;


    case INTEGER_CST:
      if (! host_integerp (bound, 0)
	  || (bound_attr == DW_AT_lower_bound
	      && (((is_c_family () || is_java ()) &&  integer_zerop (bound))
		  || (is_fortran () && integer_onep (bound)))))

	;
      else
	add_AT_unsigned (subrange_die, bound_attr, tree_low_cst (bound, 0));
      break;

    case CONVERT_EXPR:
    case NOP_EXPR:
    case NON_LVALUE_EXPR:
    case VIEW_CONVERT_EXPR:
      add_bound_info (subrange_die, bound_attr, TREE_OPERAND (bound, 0));
      break;

    case SAVE_EXPR:


      if (SAVE_EXPR_RTL (bound)
	  && (! optimize || GET_CODE (SAVE_EXPR_RTL (bound)) == MEM))
	{
	  dw_die_ref ctx = lookup_decl_die (current_function_decl);
	  dw_die_ref decl_die = new_die (DW_TAG_variable, ctx, bound);
	  rtx loc = SAVE_EXPR_RTL (bound);


	  if (GET_CODE (loc) == MEM)
	    {
	      rtx new_addr = fix_lexical_addr (XEXP (loc, 0), bound);

	      if (XEXP (loc, 0) != new_addr)
		loc = gen_rtx_MEM (GET_MODE (loc), new_addr);
	    }

	  add_AT_flag (decl_die, DW_AT_artificial, 1);
	  add_type_attribute (decl_die, TREE_TYPE (bound), 1, 0, ctx);
	  add_AT_location_description (decl_die, DW_AT_location,
				       loc_descriptor (loc));
	  add_AT_die_ref (subrange_die, bound_attr, decl_die);
	}


      break;

    case VAR_DECL:
    case PARM_DECL:
      {
	dw_die_ref decl_die = lookup_decl_die (bound);


	if (decl_die != NULL)
	  add_AT_die_ref (subrange_die, bound_attr, decl_die);
	break;
      }

    default:
      {


	dw_die_ref ctx, decl_die;
	dw_loc_descr_ref loc;

	loc = loc_descriptor_from_tree (bound, 0);
	if (loc == NULL)
	  break;

	if (current_function_decl == 0)
	  ctx = comp_unit_die;
	else
	  ctx = lookup_decl_die (current_function_decl);


	if (ctx == 0)
	  bound = build (SAVE_EXPR, TREE_TYPE (bound), bound,
			 current_function_decl, NULL_TREE);

	decl_die = new_die (DW_TAG_variable, ctx, bound);
	add_AT_flag (decl_die, DW_AT_artificial, 1);
	add_type_attribute (decl_die, TREE_TYPE (bound), 1, 0, ctx);
	add_AT_loc (decl_die, DW_AT_location, loc);

	add_AT_die_ref (subrange_die, bound_attr, decl_die);
	break;
      }
    }
}
