osinfo_list_new_same(OsinfoList *sourceOne,
                                        OsinfoList *sourceTwo)
{
    GType typeOne = G_OBJECT_TYPE(sourceOne);

    if (sourceTwo != NULL) {
        GType typeTwo = G_OBJECT_TYPE(sourceTwo);

        g_return_val_if_fail(typeOne == typeTwo, NULL);
        g_return_val_if_fail(OSINFO_IS_LIST(sourceTwo), NULL);
    }

    g_return_val_if_fail(OSINFO_IS_LIST(sourceOne), NULL);

    return g_object_new(typeOne,
                        "element-type",
                        sourceOne->priv->elementType,
                        NULL);
}
