eb_load_language(EB_Book *book)
{
    Zio zio;
    Zio_Code zio_code;
    char language_path_name[EB_MAX_PATH_LENGTH + 1];
    char language_file_name[EB_MAX_FILE_NAME_LENGTH + 1];
    char buffer[16];

    LOG(("in: eb_load_language(book=%d)", (int)book->code));

    zio_initialize(&zio);
    book->character_code = EB_CHARCODE_JISX0208;


    if (eb_find_file_name(book->path, "language", language_file_name)
	!= EB_SUCCESS)
	goto failed;

    eb_compose_path_name(book->path, language_file_name, language_path_name);
    eb_path_name_zio_code(language_path_name, ZIO_PLAIN, &zio_code);

    if (zio_open(&zio, language_path_name, zio_code) < 0)
	goto failed;


    if (zio_read(&zio, buffer, 16) != 16)
	goto failed;

    book->character_code = eb_uint2(buffer);
    if (book->character_code != EB_CHARCODE_ISO8859_1
	&& book->character_code != EB_CHARCODE_JISX0208
	&& book->character_code != EB_CHARCODE_JISX0208_GB2312) {
	goto failed;
    }

    zio_close(&zio);
    LOG(("out: eb_load_language()"));

    return;


  failed:
    zio_close(&zio);
    LOG(("out: eb_load_language()"));
}
