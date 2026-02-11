create_one_ec_pool(const std::string &pool_name, rados_t *cluster)
{
  std::string err = connect_cluster(cluster);
  if (err.length())
    return err;

  char *cmd[2];

  cmd[1] = NULL;

  cmd[0] = (char *)"{\"prefix\": \"osd erasure-code-profile set\", \"name\": \"testprofile\", \"profile\": [ \"k=2\", \"m=1\", \"ruleset-failure-domain=osd\"]}";
  int ret = rados_mon_command(*cluster, (const char **)cmd, 1, "", 0, NULL, NULL, NULL, NULL);
  if (ret) {
    rados_shutdown(*cluster);
    std::ostringstream oss;
    oss << "rados_mon_command erasure-code-profile set name:testprofile failed with error " << ret;
    return oss.str();
  }

  std::string cmdstr = "{\"prefix\": \"osd pool create\", \"pool\": \"" +
     pool_name + "\", \"pool_type\":\"erasure\", \"pg_num\":8, \"pgp_num\":8, \"erasure_code_profile\":\"testprofile\"}";
  cmd[0] = (char *)cmdstr.c_str();
  ret = rados_mon_command(*cluster, (const char **)cmd, 1, "", 0, NULL, 0, NULL, 0);
  if (ret) {
    std::ostringstream oss;

    cmd[0] = (char *)"{\"prefix\": \"osd erasure-code-profile rm\", \"name\": \"testprofile\"}";
    int ret2 = rados_mon_command(*cluster, (const char **)cmd, 1, "", 0, NULL, 0, NULL, 0);
    if (ret2)
      oss << "rados_mon_command osd erasure-code-profile rm name:testprofile failed with error " << ret2 << std::endl;

    rados_shutdown(*cluster);
    oss << "rados_mon_command erasure-code-profile set name:testprofile failed with error " << ret;
    return oss.str();
  }

  rados_wait_for_latest_osdmap(*cluster);
  return "";
}
