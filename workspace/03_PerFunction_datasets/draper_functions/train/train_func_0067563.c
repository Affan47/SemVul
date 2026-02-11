m_emit_hdr (pIIR_PredefinedProcedureDeclaration sbp, string &str, RegionStack &rstack, int l)
{
  rstack.push(sbp);

  str += "/* Prototype for predefined subprogram " + get_long_name(sbp) + " */\n";


  string proc_name = convert_string(sbp->declarator->text.to_chars(), tolower);
  if (proc_name == "deallocate") {


    str += "#define " + qid(sbp, rstack, DEFAULT) +
      "(p,a) p=(p!=NULL?(a.designated_type_info->remove(p),(void*)NULL):(void*)NULL)\n";

  } else if (proc_name == "file_open") {


    if (get_base_type(sbp->interface_declarations->first->subtype)->is(IR_FILE_TYPE)) {


      str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,n,k) file_open(f,n,k)\n";
    } else {

      str += "#define " + qid(sbp, rstack, DEFAULT) + "(s,f,n,k) file_open(s,f,n,k)\n";
    }

  } else if (proc_name == "read") {


    pIIR_Type element_type = pIIR_FileType(sbp->interface_declarations->first->subtype)->type_mark;


    if (is_array_type(element_type)) {
      if (!is_constrained_array_type(element_type))


	str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,v,l) file_read_array(f,&v,l)\n";
      else
	str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,v) file_read_array(f,&v)\n";

    } else if (get_base_type(element_type)->is(IR_RECORD_TYPE)) {
      str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,v) file_read_record(f,&v)\n";
    } else {
      string element_type_str = qid(get_base_type(element_type), rstack, TYPE);
      str += "#define " + qid(sbp, rstack, DEFAULT) +
	"(f,v) file_read_scalar(f,&v,sizeof(" + element_type_str + "))\n";
    }

  } else if (proc_name == "write") {


    pIIR_Type element_base_type =
      get_base_type(pIIR_FileType(sbp->interface_declarations->first->subtype)->type_mark);


    if (element_base_type->is(IR_ARRAY_TYPE))
      str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,v) file_write_array(f,const_pointer(v))\n";
    else if (element_base_type->is(IR_RECORD_TYPE))
      str += "#define " + qid(sbp, rstack, DEFAULT) + "(f,v) file_write_record(f,const_pointer(v))\n";
    else {
      string element_base_type_str = qid(element_base_type, rstack, TYPE);
      str += "#define " + qid(sbp, rstack, DEFAULT) +
	"(f,v) file_write_scalar(f,const_pointer(v),sizeof(" + element_base_type_str + "))\n";
    }

  } else if (proc_name == "file_close") {


    str += "#define " + qid(sbp, rstack, DEFAULT) + "(f) file_close(f)\n";

  } else
    assert(false);

  rstack.pop();
}
