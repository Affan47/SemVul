port_parser(struct nv_pair *nv, int line, plugin_conf_t * c)
{
        const char *ptr = nv->value;
        unsigned long i;


        for (i = 0; ptr[i]; i++) {
                if (!isdigit(ptr[i])) {
                        log_err("Value %s should only be numbers - line %d", nv->value, line);
                        return 1;
                }
        }


        errno = 0;
        i = strtoul(nv->value, NULL, 10);
        if (errno) {
                log_err("Error converting string to a number (%s) - line %d", strerror(errno), line);
                return 1;
        }

        c->port = i;
        return 0;

}
