seq_dict_foreach (dict_t *dict,
                  int (*fn)(char *str, void *data),
                  void *data)
{
        char index[] = "4294967296";
        int        i = 0;
        char    *val = NULL;
        int      ret = 0;

        for (;;i++) {
                snprintf(index, sizeof(index), "%d", i);
                ret = dict_get_str (dict, index, &val);
                if (ret != 0)
                        return ret == -ENOENT ? 0 : ret;
                ret = fn (val, data);
                if (ret != 0)
                        return ret;
        }
}
