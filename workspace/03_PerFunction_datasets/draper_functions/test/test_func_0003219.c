rtp_payload_type_find_format(void *obj, void *arg, int flags)
{
	struct ast_rtp_payload_type *type = obj;
	struct ast_format *format = arg;

	return (type->asterisk_format && (ast_format_cmp(&type->format, format) != AST_FORMAT_CMP_NOT_EQUAL)) ? CMP_MATCH | CMP_STOP : 0;
}
