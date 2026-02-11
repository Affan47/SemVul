queryDQ2(std::string& content,
                                    const std::string& method,
                                    const std::string& path,
                                    const std::string& post_data) const {

    MCCConfig cfg;
    usercfg.ApplyToConfig(cfg);
    ClientHTTP client(cfg, catalog, usercfg.Timeout());


    std::multimap<std::string, std::string> attrmap;
    attrmap.insert(std::pair<std::string, std::string>("User-Agent", "dqcurl"));
    ClientHTTPAttributes attrs(method, path, attrmap);
    HTTPClientInfo transfer_info;
    PayloadRaw request;
    PayloadRawInterface *response = NULL;


    if (method == "POST" && !post_data.empty()) request.Insert(post_data.c_str());

    MCC_Status r = client.process(attrs, &request, &transfer_info, &response);
    DataStatus ds = parseHTTPResponse(content, r, transfer_info, response);
    if (!ds) return ds;


    std::replace(content.begin(), content.end(), '\'', '"');
    while (content.find("None") != std::string::npos) {
      content.replace(content.find("None"), 4, "\"\"");
    }

    logger.msg(DEBUG, "DQ2 returned %s", content);
    return DataStatus::Success;
  }
