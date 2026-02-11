read_interfaces(char *filename)
{
    interfaces_file *defn;

    defn = malloc(sizeof(interfaces_file));
    if (defn == NULL) {
        return NULL;
    }
    defn->allowups = NULL;
    defn->mappings = NULL;
    defn->ifaces = NULL;

    if (!no_loopback) {
        interface_defn *lo_if = malloc(sizeof(interface_defn));
        if (!lo_if) {

            perror(filename);
            return NULL;
        }

        *lo_if = (interface_defn) {
            .logical_iface = strdup(LO_IFACE),
            .max_options = 0,
            .address_family = &addr_inet,
            .method = get_method(&addr_inet, "loopback"),
            .n_options = 0,
            .option = NULL,
            .next = NULL
        };

        defn->ifaces = lo_if;

        add_allow_up(__FILE__, __LINE__, get_allowup(&defn->allowups, "auto"), lo_if->logical_iface);
    }
    return read_interfaces_defn(defn, filename);
}
