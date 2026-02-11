m_cdfg_emit_expr (pIIR_AttrArrayFunc at, string &str, RegionStack &rstack, id_type t)
{

  if (valid_folded_value(at)) {


    str += to_string(folded_value(at).long_value());

    return true;

  } else {

    str += "(list array-attribute-call-";

    if (at->is(IR_ATTR_ARRAY_LENGTH))
      str += "length";

    else if (at->is(IR_ATTR_ARRAY_ASCENDING))
      str += "ascending";

    else if (at->is(IR_ATTR_ARRAY_LOW))
      str += "low";

    else if (at->is(IR_ATTR_ARRAY_HIGH))
      str += "high";

    else if (at->is(IR_ATTR_ARRAY_RIGHT))
      str += "right";

    else if (at->is(IR_ATTR_ARRAY_LEFT))
      str += "left";

    else
      assert(false);


    str += " " + to_string(at->index);

    if (at->array != NULL) {


      cdfg_emit_expr (at->array, str, rstack, DEFAULT);

    } else


      str += get_type_info_obj(at->array_type, rstack, false);

    str += ")";

    return false;
  }
}
