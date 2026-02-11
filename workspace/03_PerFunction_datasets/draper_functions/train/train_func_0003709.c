FontEncFind(const char *encoding_name, const char *filename)
{
    FontEncPtr encoding;
    char **alias;

    if(font_encodings == NULL) define_initial_encoding_info();

    for(encoding = font_encodings; encoding; encoding = encoding->next) {
        if(!strcasecmp(encoding->name, encoding_name))
            return encoding;
        if(encoding->aliases)
            for(alias=encoding->aliases; *alias; alias++)
                if(!strcasecmp(*alias, encoding_name))
                    return encoding;
  }


    return FontEncLoad(encoding_name, filename);
}
