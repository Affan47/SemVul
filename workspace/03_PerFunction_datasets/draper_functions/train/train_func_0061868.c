signal_info_unref (SignalInfo *info)
{
  info->base.refcount -= 1;
  if (info->base.refcount == 0)
    {
      free_arg_list (&info->args);
      base_info_free (info);
    }
}
