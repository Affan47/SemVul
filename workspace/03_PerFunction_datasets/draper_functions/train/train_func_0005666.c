PR_GetIdentitiesLayer(PRFileDesc* fd, PRDescIdentity id)
{
    PRFileDesc *layer = fd;

    if (PR_TOP_IO_LAYER == id) {
    	if (PR_IO_LAYER_HEAD == fd->identity)
			return fd->lower;
		else
			return fd;
	}

    for (layer = fd; layer != NULL; layer = layer->lower)
    {
        if (id == layer->identity) return layer;
    }
    for (layer = fd; layer != NULL; layer = layer->higher)
    {
        if (id == layer->identity) return layer;
    }
    return NULL;
}
