plugin_put(plugin_instance *this)
{
    gchar *type;

    ENTER;
    type = this->class->type;
    g_free(this);
    class_put(type);
    RET();
}
