efreet_desktop_x_field_get(Efreet_Desktop *desktop, const char *key)
{
    const char *ret;

    EINA_SAFETY_ON_NULL_RETURN_VAL(desktop, NULL);
    EINA_SAFETY_ON_NULL_RETURN_VAL(desktop->x, NULL);
    EINA_SAFETY_ON_TRUE_RETURN_VAL(strncmp(key, "X-", 2), NULL);

    ret = eina_hash_find(desktop->x, key);
    if (!ret)
        return NULL;

    return eina_stringshare_add(ret);
}
