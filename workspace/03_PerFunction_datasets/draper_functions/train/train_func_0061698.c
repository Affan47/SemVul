write_float_array(gs_param_list *plist, const char *key, const float *values,
                  int count)
{
    if (count != 0) {
        gs_param_float_array fa;

        fa.persistent = false;
        fa.size = count;
        fa.data = values;
        return param_write_float_array(plist, key, &fa);
    }
    return 0;
}
