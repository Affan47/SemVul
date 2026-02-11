conf_validate_port(cfg_t *cfg, cfg_opt_t *opt)
{
    int value = cfg_opt_getnint(opt, 0);
    if(value <= 0)
    {
        cfg_error(cfg, "invalid port %d in section '%s'", value, cfg_name(cfg));
        return -1;
    }
    return 0;
}
