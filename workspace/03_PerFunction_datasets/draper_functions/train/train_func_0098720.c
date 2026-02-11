connect_cluster(rados_t *cluster)
{
  char *id = getenv("CEPH_CLIENT_ID");
  if (id) std::cerr << "Client id is: " << id << std::endl;

  int ret;
  ret = rados_create(cluster, NULL);
  if (ret) {
    std::ostringstream oss;
    oss << "rados_create failed with error " << ret;
    return oss.str();
  }
  ret = rados_conf_read_file(*cluster, NULL);
  if (ret) {
    rados_shutdown(*cluster);
    std::ostringstream oss;
    oss << "rados_conf_read_file failed with error " << ret;
    return oss.str();
  }
  rados_conf_parse_env(*cluster, NULL);
  ret = rados_connect(*cluster);
  if (ret) {
    rados_shutdown(*cluster);
    std::ostringstream oss;
    oss << "rados_connect failed with error " << ret;
    return oss.str();
  }
  return "";
}
