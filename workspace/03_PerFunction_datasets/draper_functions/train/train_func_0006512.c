xlator_option_validate_percent (xlator_t *xl, const char *key, const char *value,
                                volume_option_t *opt, char **op_errstr)
{
        double    percent = 0;
        int       ret = -1;
        char      errstr[256];


        if (gf_string2percent (value, &percent) != 0) {
                snprintf (errstr, 256,
                          "invalid percent format \"%s\" in \"option %s\"",
                          value, key);
                gf_log (xl->name, GF_LOG_ERROR, "%s", errstr);
                goto out;
        }

        if ((percent < 0.0) || (percent > 100.0)) {
                snprintf (errstr, 256,
                          "'%lf' in 'option %s %s' is out of range [0 - 100]",
                          percent, key, value);
                gf_log (xl->name, GF_LOG_ERROR, "%s", errstr);
                goto out;
        }

        ret = 0;
out:
        if (ret && op_errstr)
                *op_errstr = gf_strdup (errstr);
        return ret;
}
