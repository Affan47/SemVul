color_destroy(color_t* color)
{
    g_list_foreach(color->ext, (GFunc)g_free, NULL);
    if (color->gc) g_object_unref(G_OBJECT(color->gc));
    g_free(color);
}
