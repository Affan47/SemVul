_ipmi_i2c_smbus_access (ipmi_ssif_ctx_t ctx,
                        int dev_fd,
                        char read_write,
                        uint8_t command,
                        union ipmi_i2c_smbus_data *data)
{
  struct ipmi_i2c_smbus_ioctl_data args;
  fd_set read_fds;
  struct timeval tv;
  int n, rv;

  assert (ctx);
  assert (ctx->magic == IPMI_SSIF_CTX_MAGIC);

  if (read_write == IPMI_I2C_SMBUS_READ)
    {
      FD_ZERO (&read_fds);
      FD_SET (dev_fd, &read_fds);

      tv.tv_sec = IPMI_SSIF_TIMEOUT;
      tv.tv_usec = 0;

      if ((n = select (dev_fd + 1,
                       &read_fds,
                       NULL,
                       NULL,
                       &tv)) < 0)
        {
          SSIF_ERRNO_TO_SSIF_ERRNUM (ctx, errno);
          return (-1);
        }

      if (!n)
        {

          SSIF_SET_ERRNUM (ctx, IPMI_SSIF_ERR_DRIVER_TIMEOUT);
          return (-1);
        }
    }

  args.read_write = read_write;
  args.command = command;
  args.size = IPMI_I2C_SMBUS_BLOCK_DATA;
  args.data = data;

  if ((rv = ioctl (dev_fd, IPMI_I2C_SMBUS, &args)) < 0)
    {
      SSIF_ERRNO_TO_SSIF_ERRNUM (ctx, errno);
      return (-1);
    }

  return (rv);
}
