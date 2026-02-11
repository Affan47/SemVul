qof_commit_edit (QofInstance *inst)
{
    QofInstancePrivate *priv;

    if (!inst) return FALSE;

    priv = GET_PRIVATE(inst);
    priv->editlevel--;
    if (0 < priv->editlevel) return FALSE;

    if (0 > priv->editlevel)
    {
        PERR ("unbalanced call - resetting (was %d)", priv->editlevel);
        priv->editlevel = 0;
    }
    return TRUE;
}
