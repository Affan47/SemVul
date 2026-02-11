pmap_registry_search_by_port (xlator_t *this, int port)
{
        struct pmap_registry *pmap = NULL;
        char *brickname = NULL;

        if (port > 65535)
                goto out;

        pmap = pmap_registry_get (this);

        if (pmap->ports[port].type == GF_PMAP_PORT_BRICKSERVER)
                brickname = pmap->ports[port].brickname;

out:
        return brickname;
}
