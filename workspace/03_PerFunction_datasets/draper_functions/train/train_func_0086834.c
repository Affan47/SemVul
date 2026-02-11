_init_sunbmc_ipmi (void)
{
  if (!(sunbmc_ctx = ipmi_sunbmc_ctx_create ()))
    {
      _bmclog ("ipmi_sunbmc_ctx_create: %s", strerror (errno));
      return (-1);
    }

  if (cmd_args.common.driver_device)
    {
      if (ipmi_sunbmc_ctx_set_driver_device (sunbmc_ctx,
                                             cmd_args.common.driver_device) < 0)
        {
          _bmclog ("ipmi_sunbmc_ctx_set_driver_device: %s",
                   ipmi_sunbmc_ctx_strerror (ipmi_sunbmc_ctx_errnum (sunbmc_ctx)));
          return (-1);
        }
    }

  if (ipmi_sunbmc_ctx_io_init (sunbmc_ctx) < 0)
    {
      _bmclog ("ipmi_sunbmc_ctx_io_init: %s",
               ipmi_sunbmc_ctx_strerror (ipmi_sunbmc_ctx_errnum (sunbmc_ctx)));
      return (-1);
    }

  return (0);
}
