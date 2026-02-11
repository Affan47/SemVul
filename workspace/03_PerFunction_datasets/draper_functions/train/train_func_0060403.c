fserve_client_destroy(fserve_t *fclient)
{
    if (fclient)
    {
        if (fclient->file)
            fclose (fclient->file);

        if (fclient->callback)
            fclient->callback (fclient->client, fclient->arg);
        else
            if (fclient->client)
                client_destroy (fclient->client);
        free (fclient);
    }
}
