_interpret_config_sel_destroy (ipmi_interpret_ctx_t ctx,
                               struct ipmi_interpret_sel_config **config)
{
  unsigned int i = 0;

  assert (ctx);
  assert (ctx->magic == IPMI_INTERPRET_CTX_MAGIC);

  if (config)
    {
      while (config[i])
        {
          free (config[i]);
          i++;
        }
      free (config);
    }
}
