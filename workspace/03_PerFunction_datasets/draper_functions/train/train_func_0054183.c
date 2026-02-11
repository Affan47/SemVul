emit_init_func (pIIR_LibraryUnit l, string &str, const string &body,
		RegionStack &rstack)
{
  string lid = qid (l, rstack, id_type());


  last_pos_info = emit_posinfo (NO_SOURCE_LINE, str, last_pos_info, 0);

  if (l->continued)
    str += "int " + qid (l->continued, rstack, id_type ()) + "_init ();\n";
  for (pIIR_LibraryUnitList ul = l->used_units; ul; ul = ul->rest)
    if (ul->first != l->continued)
      str += "int " + qid (ul->first, rstack, id_type ()) + "_init ();\n";

  str += "bool " + lid + "_init_done = false;\n";
  str += "int " + lid + "_init(){\n";
  str += "if (" + lid + "_init_done) return 1;\n";
  str += lid + "_init_done=true;\n";


  if (l->continued)
    str += qid (l->continued, rstack, id_type ()) + "_init ();\n";
  for (pIIR_LibraryUnitList ul = l->used_units; ul; ul = ul->rest)
    if (ul->first != l->continued)
      str += qid (ul->first, rstack, id_type ()) + "_init ();\n";

  emit_source_file_register_code(l, str, rstack, 0);

  str += "name_stack iname;\n";
  str += "iname.push(\"\");\n";
  str += body;
  str += "iname.pop();\n";

  if (l->is (IR_PACKAGE_DECLARATION))
    {


      str += "handle_info *h = get_handle (\"" +
	string (l->library_name->text.to_chars()) +
	"\",\"" +  nid (l, BARE) + "\",NULL);\n";
      str += "if (h != NULL) (*h->init_function) ();\n";
    }

  str += "return 1;\n";
  str += "}\n";

  if (l->is (IR_PACKAGE_BODY_DECLARATION))
    {
      pIIR_PackageBodyDeclaration pb = (pIIR_PackageBodyDeclaration)l;
      str += "/* handle for simulator to find package body initialization function */\n";
      str += "handle_info *";
      str += qid (pb, rstack, id_type());
      str += "_hinfo =\n";
      str += "  add_handle(\"";
      str += string (pb->package->library_name->text.to_chars()) + "\",\"" +  nid (pb->package, BARE) + "\",NULL";
      str += ",NULL";
      str += ",&" + qid (pb, rstack, id_type()) + "_init);\n";
    }

}
