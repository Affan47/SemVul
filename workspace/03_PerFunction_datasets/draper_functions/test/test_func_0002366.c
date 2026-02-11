xlator_get_option (xlator_t *xl, char *key, char **value)
{
        GF_ASSERT (xl);
        return dict_get_str (xl->options, key, value);
}
