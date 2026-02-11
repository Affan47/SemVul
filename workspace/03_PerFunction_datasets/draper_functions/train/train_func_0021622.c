m_emit_impl (pIIR_ScalarSubtype sst, string &str, RegionStack &rstack, int l)
{
  pIIR_TypeDeclaration decl = sst->declaration;


  if (sst->range == NULL && sst->resolution_function == NULL) {


  } else if (sst->base->is(IR_ENUMERATION_TYPE)) {


    vector<RangeDescriptor> range_desc = get_discrete_range(sst, rstack, IR_NOT_STATIC);

    StaticRangeDescriptor<string, string> range =
      range_desc[0].rangedes_to_string(rstack, get_default_id_type(rstack));
    if (and_reduce(range.valid)) {


      last_pos_info = emit_posinfo(NO_SOURCE_LINE, str, last_pos_info, l);

      str += "/* Implementation of enumeration type " + get_long_name(decl) + " */\n";
      str += "const char **" + qid(decl, rstack, INFO) + "::values=" +
	"((enum_info_base&)" + qid(decl, rstack, INFO) + "_INFO).values=" +
	"&" + qid(sst->base->declaration, rstack, INFO) + "_INFO.get_values()[" + range.left + "];\n";
    }

  } else if (sst->base->is(IR_PHYSICAL_TYPE)) {
    pIIR_PhysicalType pt = pIIR_PhysicalType (sst->base);


    last_pos_info = emit_posinfo(NO_SOURCE_LINE, str, last_pos_info, l);

    str += ("/* Implementation of physical base type " +
	    get_long_name(decl) + " */\n");

    string pt_qid = qid (pt, rstack, INFO);

    str += "const char *" + pt_qid + "::units[] = {\n";
    int unit_count = 0;
    for (pIIR_UnitList ul = pt->units; ul; ul = ul->rest)
      {
	str += "  \"" + nid (ul->first, BARE) + "\"";
	if (ul->rest)
	  str += ",\n";
	unit_count++;
      }
    str += "\n};\n";

    str += "const lint " + pt_qid + "::scale[] = {\n";
    string scale_string = "1LL";
    str += "  " + scale_string;
    for (pIIR_UnitList ul = pt->units->rest; ul; ul = ul->rest)
      {
	pIIR_PhysicalUnit u = ul->first;
	string this_scale = "";
	emit_expr (u->multiplier, this_scale, rstack, DEFAULT);
	scale_string = this_scale + "*(" + scale_string + ")";
	str += ",\n  " + scale_string;
      }
    str += "\n};\n";

    str += ("const int " + pt_qid + "::unit_count = " + to_string (unit_count)
	    + ";\n");

  } else if (sst->base->is(IR_INTEGER_TYPE) ||
	     sst->base->is(IR_FLOATING_TYPE)) {


  } else
    codegen_error.error("%:error: sorry, this subtype declaration is currently not supported", sst);
}
