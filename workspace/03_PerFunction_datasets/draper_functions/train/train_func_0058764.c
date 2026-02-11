any_trusted_dir_is_v1_authority(void)
{
  if (trusted_dir_servers)
    return get_n_authorities(V1_DIRINFO) > 0;

  return 0;
}
