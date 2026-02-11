gvplugin_install(GVC_t * gvc, api_t api, const char *typestr,
                         int quality, gvplugin_package_t * package, gvplugin_installed_t * typeptr)
{
    gvplugin_available_t *plugin, **pnext;
#define TYPSIZ 63
    char *p, pins[TYPSIZ + 1], pnxt[TYPSIZ + 1];

    strncpy(pins, typestr, TYPSIZ);
    if ((p = strchr(pins, ':')))
        *p = '\0';


    pnext = &(gvc->apis[api]);


    while (*pnext) {
        strncpy(pnxt, (*pnext)->typestr, TYPSIZ);
        if ((p = strchr(pnxt, ':')))
            *p = '\0';
        if (strcmp(pins, pnxt) <= 0)
            break;
        pnext = &((*pnext)->next);
    }


    while (*pnext) {
        strncpy(pnxt, (*pnext)->typestr, TYPSIZ);
        if ((p = strchr(pnxt, ':')))
            *p = '\0';
        if (strcmp(pins, pnxt) != 0)
            break;
        if (quality >= (*pnext)->quality)
            break;
        pnext = &((*pnext)->next);
    }

    plugin = GNEW(gvplugin_available_t);
    plugin->next = *pnext;
    *pnext = plugin;
    plugin->typestr = typestr;
    plugin->quality = quality;
    plugin->package = package;
    plugin->typeptr = typeptr;

    return TRUE;
}
