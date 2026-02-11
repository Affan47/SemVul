rtp_payload_type_hash(const void *obj, const int flags)
{
	const struct ast_rtp_payload_type *type = obj;
	const int *payload = obj;

	return (flags & OBJ_KEY) ? *payload : type->payload;
}
