translate_postscript_fontname(char* fontname)
{
    static PostscriptAlias key;
    static PostscriptAlias *result;

    if (key.name == NULL || strcasecmp(key.name, fontname)) {
        key.name = fontname;
        result = (PostscriptAlias *) bsearch((void *) &key,
			(void *) postscript_alias,
			sizeof(postscript_alias) / sizeof(PostscriptAlias),
			sizeof(PostscriptAlias),
                        fontcmpf);
    }
    return result;
}
