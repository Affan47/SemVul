bt_bencode_str(torrent_ctx* ctx, const char* name, const char* str)
{
	size_t len = strlen(str);
	int num_len;
	char* p;

	if(name) bt_str_append(ctx, name);
	if(!bt_str_ensure_length(ctx, ctx->torrent_length + len + 21)) return;

	p = ctx->torrent_str + ctx->torrent_length;
	p += (num_len = rhash_sprintI64(p, len));
	ctx->torrent_length += len + num_len + 1;

	*(p++) = ':';
	memcpy(p, str, len + 1);
}
