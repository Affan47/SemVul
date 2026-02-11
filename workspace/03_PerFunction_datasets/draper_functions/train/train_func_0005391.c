osinfo_tree_set_property(GObject      *object,
                         guint         property_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
    OsinfoTree *tree = OSINFO_TREE(object);

    switch (property_id) {
    case PROP_ARCHITECTURE:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_ARCHITECTURE,
                                g_value_get_string(value));
        break;

    case PROP_URL:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_URL,
                                g_value_get_string(value));
        break;

    case PROP_TREEINFO_FAMILY:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_TREEINFO_FAMILY,
                                g_value_get_string(value));
        break;

    case PROP_TREEINFO_VARIANT:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_TREEINFO_VARIANT,
                                g_value_get_string(value));
        break;

    case PROP_TREEINFO_VERSION:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_TREEINFO_VERSION,
                                g_value_get_string(value));
        break;

    case PROP_TREEINFO_ARCH:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_TREEINFO_ARCH,
                                g_value_get_string(value));
        break;

    case PROP_KERNEL_PATH:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_KERNEL,
                                g_value_get_string(value));
        break;

    case PROP_INITRD_PATH:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_INITRD,
                                g_value_get_string(value));
        break;

    case PROP_BOOT_ISO_PATH:
        osinfo_entity_set_param(OSINFO_ENTITY(tree),
                                OSINFO_TREE_PROP_BOOT_ISO,
                                g_value_get_string(value));
        break;

    default:

        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
