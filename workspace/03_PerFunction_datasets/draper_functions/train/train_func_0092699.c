find_site_cookie_mozilla_v3(
    void* cookie, int , char **argv, char **
) {
    MOZILLA_COOKIE_SQL* _cookie = (MOZILLA_COOKIE_SQL*)cookie;
    char host[256], cookie_name[256], cookie_value[256];
    long long expires;


    strcpy(host, "");
    strcpy(cookie_name, "");
    strcpy(cookie_value, "");
    expires = 0;

    sscanf( argv[0], "%255s", host );
    sscanf( argv[1], "%255s", cookie_name );
    sscanf( argv[2], "%255s", cookie_value );
    sscanf( argv[3],
#ifdef _WIN32
        "%I64d",
#elif defined(__APPLE__)
        "%lld",
#else
        "%Ld",
#endif
        &expires
    );


    if (starts_with(host, "#HttpOnly")) return 0;


    if (!strstr(host, _cookie->host.c_str())) return 0;


    if (time(0) > expires) return 0;


    if (starts_with(cookie_name, _cookie->name)) {
        _cookie->value = cookie_value;
    }

    return 0;
}
