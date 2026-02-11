php_cli_server_chunk_heap_new(char *block, char *buf, size_t len)
{
	php_cli_server_chunk *chunk = pemalloc(sizeof(php_cli_server_chunk), 1);
	if (!chunk) {
		return NULL;
	}

	chunk->type = PHP_CLI_SERVER_CHUNK_HEAP;
	chunk->next = NULL;
	chunk->data.heap.block = block;
	chunk->data.heap.p = buf;
	chunk->data.heap.len = len;
	return chunk;
}
