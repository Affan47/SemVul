chewing_new()
{
	ChewingContext *ctx;
	int ret;
	char search_path[PATH_MAX];
	char path[PATH_MAX];

	ctx = ALC( ChewingContext, 1 );
	if ( !ctx )
		goto error;

	ctx->output = ALC ( ChewingOutput, 1 );
	if ( !ctx->output )
		goto error;

	ctx->data = allocate_ChewingData();
	if ( !ctx->data )
		goto error;

	chewing_Reset( ctx );

	ret = get_search_path( search_path, sizeof( search_path ) );
	if ( ret )
		goto error;

	ret = find_path_by_files(
		search_path, CHAR_FILES, path, sizeof( path ) );
	if ( ret )
		goto error;
	ret = InitChar( ctx->data, path );
	if ( ret )
		goto error;

	ret = find_path_by_files(
		search_path, DICT_FILES, path, sizeof( path ) );
	if ( ret )
		goto error;
	ret = InitDict( ctx->data, path );
	if ( ret )
		goto error;
	ret = InitTree( ctx->data, path );
	if ( ret )
		goto error;

	ret = InitHash( ctx->data );
	if ( !ret )
		goto error;

	ctx->cand_no = 0;

	ret = find_path_by_files(
		search_path, SYMBOL_TABLE_FILES, path, sizeof( path ) );
	if ( ret )
		goto error;
	ret = InitSymbolTable( ctx->data, path );
	if ( ret )
		goto error;

	ret = find_path_by_files(
		search_path, EASY_SYMBOL_FILES, path, sizeof( path ) );
	if ( ret )
		goto error;
	ret = InitEasySymbolInput( ctx->data, path );
	if ( ret )
		goto error;

	ret = find_path_by_files(
		search_path, PINYIN_FILES, path, sizeof( path ) );
	if ( ret )
		goto error;
	ret = InitPinyin( ctx->data, path );
	if ( !ret )
		goto error;

	return ctx;
error:
	chewing_delete( ctx );
	return NULL;
}
