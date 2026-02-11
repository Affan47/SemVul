create_template_pathname(const char *name, char *buf, size_t size) {


    if (*name == '/')
        snprintf(buf, size, "%s/%s%s", settings.localdir, settings.templatedir, name);
    else
        snprintf(buf, size, "%s/%s/%s", settings.localdir, settings.templatedir, name);
}
