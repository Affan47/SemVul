emit_noqual_id (pIIR_Declaration d, string &str, RegionStack &rstack, id_type obj_access)
{
  if (d->declarator)
    {
      if (d->is(IR_ENUMERATION_LITERAL) && codegen_options.get_verbose ())
	{
	  emit_noqual_id (pIIR_EnumerationLiteral(d)->subtype->declaration, str, rstack);
	  str += "_";
	  if (d->declarator->is(IR_CHARACTER_LITERAL))
	    {
	      IR_Character ch = d->declarator->text[1];
	      if (isalnum(ch))
		str += ch;
	      else
		str += unsigned(ch);
	    }
	  else
	    str += nid(d, obj_access);
	}
      else
	{
	  str += nid(d, obj_access);

	  if (d->is(IR_SUBPROGRAM_DECLARATION) && codegen_options.get_verbose ())
	    {
	      for(pIIR_InterfaceList il =
		    pIIR_SubprogramDeclaration(d)->interface_declarations;
		  il; il = il->rest)
		{
		  str += "__";
		  str += qid (il->first->subtype->declaration, rstack, id_type());
		}
	      if(d->is(IR_FUNCTION_DECLARATION))
		{
		  str += "__";
		  str += qid (pIIR_FunctionDeclaration(d)->return_type->declaration, rstack, id_type());
		}
	    }
	}
    }
  else
    str += "<anonymous>";
}
