bt_enum_unsigned_insert_range_to_quark(struct declaration_enum *enum_declaration,
                        uint64_t start, uint64_t end, GQuark q)
{
	struct enum_range_to_quark *rtoq;

	rtoq = g_new(struct enum_range_to_quark, 1);
	bt_list_add(&rtoq->node, &enum_declaration->table.range_to_quark);
	rtoq->range.start._unsigned = start;
	rtoq->range.end._unsigned = end;
	rtoq->quark = q;
}
