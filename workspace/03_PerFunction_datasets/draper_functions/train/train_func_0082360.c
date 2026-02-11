CacheCheck(Arc::XMLNode in, Arc::XMLNode out, const Arc::User& mapped_user) {


  ARex::CacheConfig cache_params(config.CacheParams());
  cache_params.substitute(config, mapped_user);
  Arc::FileCache cache(cache_params.getCacheDirs(), "0", mapped_user.get_uid(), mapped_user.get_gid());
  if (!cache) {
    logger.msg(Arc::ERROR, "Error creating cache");
    return Arc::MCC_Status(Arc::GENERIC_ERROR, "CacheCheck", "Server error with cache");
  }

  Arc::XMLNode resp = out.NewChild("CacheCheckResponse");
  Arc::XMLNode results = resp.NewChild("CacheCheckResult");

  for(int n = 0;;++n) {
    Arc::XMLNode id = in["CacheCheck"]["TheseFilesNeedToCheck"]["FileURL"][n];

    if (!id) break;

    std::string fileurl = (std::string)in["CacheCheck"]["TheseFilesNeedToCheck"]["FileURL"][n];
    Arc::XMLNode resultelement = results.NewChild("Result");
    bool fileexist = false;
    std::string file_lfn;
    Arc::initializeCredentialsType cred_type(Arc::initializeCredentialsType::SkipCredentials);
    Arc::UserConfig usercfg(cred_type);
    Arc::URL url(fileurl);
    Arc::DataHandle d(url, usercfg);

    logger.msg(Arc::INFO, "Looking up URL %s", d->str());

    file_lfn = cache.File(d->str());
    if (file_lfn.empty()) {
      logger.msg(Arc::ERROR, "Empty filename returned from FileCache");
      resultelement.NewChild("ExistInTheCache") = "false";
      resultelement.NewChild("FileSize") = "0";
      continue;
    }
    logger.msg(Arc::INFO, "Cache file is %s", file_lfn);

    struct stat fileStat;

    if (Arc::FileStat(file_lfn, &fileStat, false))
      fileexist = true;
    else if (errno != ENOENT)
      logger.msg(Arc::ERROR, "Problem accessing cache file %s: %s", file_lfn, Arc::StrError(errno));

    resultelement.NewChild("FileURL") = fileurl;
    resultelement.NewChild("ExistInTheCache") = (fileexist ? "true": "false");
    if (fileexist)
      resultelement.NewChild("FileSize") = Arc::tostring(fileStat.st_size);
    else
      resultelement.NewChild("FileSize") = "0";
  }
  return Arc::MCC_Status(Arc::STATUS_OK);
}
