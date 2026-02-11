pmap_registry_remove (xlator_t *this, int port, const char *brickname,
                      gf_pmap_port_type_t type, void *xprt)
{
        struct pmap_registry *pmap = NULL;
        int                   p = 0;
        glusterd_conf_t      *priv = NULL;

        priv = this->private;
        pmap = priv->pmap;
        if (!pmap)
                goto out;

        if (port) {
                if (port > 65535)
                        goto out;

                p = port;
                goto remove;
        }

        if (brickname && strchr (brickname, '/')) {
                p = pmap_registry_search (this, brickname, type);
                if (p)
                        goto remove;
        }

        if (xprt) {
                p = pmap_registry_search_by_xprt (this, xprt, type);
                if (p)
                        goto remove;
        }

        goto out;
remove:
        gf_log ("pmap", GF_LOG_INFO, "removing brick %s on port %d",
                pmap->ports[p].brickname, p);

        if (pmap->ports[p].brickname)
                free (pmap->ports[p].brickname);

        pmap->ports[p].brickname = NULL;
        pmap->ports[p].xprt = NULL;

out:
        return 0;
}
