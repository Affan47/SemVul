try_open(ca_context *c, const char *t) {
        char *mn;
        struct private_dso *p;

        p = PRIVATE_DSO(c);

        if (!(mn = ca_sprintf_malloc(CA_PLUGIN_PATH "/libcanberra-%s", t)))
                return CA_ERROR_OOM;

        errno = 0;
        p->module = lt_dlopenext(mn);
        ca_free(mn);

        if (!p->module) {
                int ret;

                if (errno == ENOENT)
                        ret = CA_ERROR_NOTFOUND;
                else
                        ret = ca_error_from_string(lt_dlerror());

                if (ret == CA_ERROR_NOTFOUND)
                        ret = CA_ERROR_NODRIVER;

                return ret;
        }

        return CA_SUCCESS;
}
