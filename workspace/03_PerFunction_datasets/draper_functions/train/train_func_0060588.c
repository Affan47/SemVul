record_io_unit_id(Token *id)
{
     if( id->tclass == '*' )
     {
	  current_io_unit_id = IO_UNIT_DEFAULT;
     }
     else if( is_true(ID_EXPR,id->TOK_flags)){
	  current_io_unit_id = id->value.integer;
     }
     else if( is_true(LIT_CONST,id->TOK_flags) &&
	      id->TOK_type == type_byte(class_VAR,type_INTEGER))
     {
	  current_io_unit_no = id->value.integer;
     }
}
