get(const std::string& id) const {
  if(id == "LOCALIP") return local_ip_;
  if(id == "LOCALPORT") return local_port_;
  if(id == "REMOTEIP") return remote_ip_;
  if(id == "REMOTEPORT") return remote_port_;
  return "";
}
