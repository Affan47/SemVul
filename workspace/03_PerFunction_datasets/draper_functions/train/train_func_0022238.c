ast_rtp_instance_available_formats(struct ast_rtp_instance *instance, struct ast_format_cap *to_endpoint, struct ast_format_cap *to_asterisk, struct ast_format_cap *result)
{
	if (instance->engine->available_formats) {
		instance->engine->available_formats(instance, to_endpoint, to_asterisk, result);
		if (!ast_format_cap_is_empty(result)) {
			return;
		}
	}

	ast_translate_available_formats(to_endpoint, to_asterisk, result);
}
