awt_open_ACISRT_URL_by_gbd(AW_root *aw_root,GBDATA *gb_main, GBDATA *gbd, const char *name, const char *url_srt){
    GB_ERROR        error = 0;
    GB_transaction  tscope(gb_main);
    char           *url   = GB_command_interpreter(gb_main,name,url_srt,gbd, 0);

    if (!url) error = GB_await_error();
    else error      = awt_openURL(aw_root, gb_main, url);

    free(url);

    return error;
}
