set_tex_use_pdf (const char *prog)
{
    const char *p = strrchr(prog, SLASH);
    char test[4];


    p = (p == NULL)? prog : p + 1;

    *test = '\0';
    strncat(test, p, 3);
    gretl_lower(test);
    use_pdf = !strcmp(test, "pdf");
}
