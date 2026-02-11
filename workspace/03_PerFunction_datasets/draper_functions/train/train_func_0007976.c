clear_pw_enc( const char *pwd )
{

    if (!pwd)
        return NULL;


    if ((*pwd == PWD_HASH_PREFIX_START) && (pwd == PL_strcasestr( pwd, "{clear}" ))) {
        return( slapi_ch_strdup( pwd + 7 ));
    } else {
        return( slapi_ch_strdup( pwd ));
    }
}
