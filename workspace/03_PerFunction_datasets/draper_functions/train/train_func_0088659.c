ast_rtp_codecs_payloads_clear(struct ast_rtp_codecs *codecs, struct ast_rtp_instance *instance)
{
	ast_rtp_codecs_payloads_destroy(codecs);

	if (instance && instance->engine && instance->engine->payload_set) {
		int i;
		for (i = 0; i < AST_RTP_MAX_PT; i++) {
			instance->engine->payload_set(instance, i, 0, NULL, 0);
		}
	}

	ast_rtp_codecs_payloads_initialize(codecs);
}
