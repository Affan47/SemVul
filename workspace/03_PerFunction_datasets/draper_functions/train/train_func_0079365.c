dispose (GObject *object)
{
    CutELFLoaderPrivate *priv = CUT_ELF_LOADER_GET_PRIVATE(object);

    if (priv->so_filename) {
        g_free(priv->so_filename);
        priv->so_filename = NULL;
    }

    if (priv->content) {
        g_free(priv->content);
        priv->content = NULL;
    }

    G_OBJECT_CLASS(cut_elf_loader_parent_class)->dispose(object);
}
