arcrename(const Arc::URL& old_url,
               const Arc::URL& new_url,
               Arc::UserConfig& usercfg,
               int timeout) {

  if (!old_url) {
    logger.msg(Arc::ERROR, "Invalid URL: %s", old_url.str());
    return false;
  }
  if (!new_url) {
    logger.msg(Arc::ERROR, "Invalid URL: %s", new_url.str());
    return false;
  }


  if (old_url.Protocol() != new_url.Protocol() ||
      old_url.Host() != new_url.Host() ||
      old_url.Port() != new_url.Port()) {
    logger.msg(Arc::ERROR, "Both URLs must have the same protocol, host and port");
    return false;
  }
  std::string old_path(old_url.Path());
  std::string new_path(new_url.Path());
  Arc::CanonicalDir(old_path, true);
  Arc::CanonicalDir(new_path, true);

  if ((old_path.find_first_not_of('/') == std::string::npos && old_url.MetaDataOptions().empty()) ||
      new_path.find_first_not_of('/') == std::string::npos) {
    logger.msg(Arc::ERROR, "Cannot rename to or from root directory");
    return false;
  }
  if (old_path == new_path && old_url.FullPath() == new_url.FullPath()) {
    logger.msg(Arc::ERROR, "Cannot rename to the same URL");
    return false;
  }

  Arc::DataHandle url(old_url, usercfg);
  if (!url) {
    logger.msg(Arc::ERROR, "Unsupported URL given");
    return false;
  }
  if (url->RequiresCredentials()) {
    if (usercfg.ProxyPath().empty() ) {
      logger.msg(Arc::ERROR, "Unable to rename %s: No valid credentials found", old_url.str());
      return false;
    }
    Arc::Credential holder(usercfg.ProxyPath(), "", "", "");
    if (holder.GetEndTime() < Arc::Time()){
      logger.msg(Arc::ERROR, "Proxy expired");
      logger.msg(Arc::ERROR, "Unable to rename %s: No valid credentials found", old_url.str());
      return false;
    }
  }


  url->SetSecure(false);


  Arc::DataStatus res = url->Rename(new_url);
  if (!res.Passed()) {
    logger.msg(Arc::ERROR, std::string(res));
    if (res.Retryable())
      logger.msg(Arc::ERROR, "This seems like a temporary error, please try again later");
    return false;
  }
  return true;
}
