_sql(Request& r, MethodParams& params) {
	Value& statement=params.as_junction(0, "statement must be code");

	HashStringValue* bind=0;
	ulong limit=SQL_NO_LIMIT;
	ulong offset=0;
	if(params.count()>1)
		if(HashStringValue* options=params.as_hash(1, "sql options")) {
			int valid_options=0;
			if(Value* vbind=options->get(sql_bind_name)) {
				valid_options++;
				bind=vbind->get_hash();
			}
			if(Value* vlimit=options->get(sql_limit_name)) {
				valid_options++;
				limit=(ulong)r.process_to_value(*vlimit).as_double();
			}
			if(Value* voffset=options->get(sql_offset_name)) {
				valid_options++;
				offset=(ulong)r.process_to_value(*voffset).as_double();
			}
			if(valid_options!=options->count())
				throw Exception(PARSER_RUNTIME, 0, CALLED_WITH_INVALID_OPTION);
		}

	SQL_Driver::Placeholder* placeholders=0;
	uint placeholders_count=0;
	if(bind)
		placeholders_count=marshal_binds(*bind, placeholders);

	Temp_lang temp_lang(r, String::L_SQL);
	const String&  statement_string=r.process_to_string(statement);
	const char* statement_cstr=statement_string.untaint_cstr(r.flang, r.connection());

	Table_sql_event_handlers handlers;

	r.connection()->query(
		statement_cstr,
		placeholders_count, placeholders,
		offset, limit,
		handlers,
		statement_string);

	if(bind)
		unmarshal_bind_updates(*bind, placeholders_count, placeholders);

	Table& result=
		handlers.table?*handlers.table:
		*new Table(Table::columns_type(0));


	GET_SELF(r, VTable).set_table(result);
}
