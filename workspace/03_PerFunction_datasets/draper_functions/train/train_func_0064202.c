next_attr(const char **pos, const char *end, const char **key_out,
          const char **val_out)
{
    const char *key, *key_end, *val, *val_end;

    *key_out = *val_out = NULL;
    if (*pos == end)
        return FALSE;
    key = *pos;
    key_end = memchr(key, '\0', end - key);
    if (key_end == NULL)
        return FALSE;
    val = key_end + 1;
    val_end = memchr(val, '\0', end - val);
    if (val_end == NULL)
        return FALSE;

    *key_out = key;
    *val_out = val;
    *pos = val_end + 1;
    return TRUE;
}
