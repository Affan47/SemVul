r600_cs_parser_fini(struct radeon_cs_parser *parser, int error)
{
	unsigned i;

	kfree(parser->relocs);
	for (i = 0; i < parser->nchunks; i++)
		drm_free_large(parser->chunks[i].kdata);
	kfree(parser->chunks);
	kfree(parser->chunks_array);
}
