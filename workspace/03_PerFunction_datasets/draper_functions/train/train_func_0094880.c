possible_switch_expr_type(pIIR_Type t)
{
    if(t == NULL)
	return false;
    pIIR_Type bt = vaul_get_base (t);

    if(bt->is(IR_SCALAR_TYPE) ||
       bt->is(IR_ENUMERATION_TYPE))
	return true;
    if(!bt->is(IR_ARRAY_TYPE))
	return false;

    pIIR_ArrayType at = pIIR_ArrayType(bt);
    if(!at->index_types || at->index_types->rest)
	return false;
    return is_character_type(at->element_type);
}
