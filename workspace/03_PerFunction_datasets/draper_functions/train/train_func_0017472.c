fetion_group_create(gint id, const gchar *name)
{
    fetion_group *group;

    g_return_val_if_fail(name != NULL, NULL);

    group = g_new0(fetion_group, 1);
    group->group_id = id;
    group->group_name = g_strdup(name);

    return group;
}
