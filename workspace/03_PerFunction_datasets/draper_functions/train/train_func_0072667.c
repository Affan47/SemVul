resolveLocations(std::list<std::string>& sites) {


    {
      Glib::Mutex::Lock l(dq2_cache_lock);
      if (dq2_cache.dataset_locations.find(dataset) != dq2_cache.dataset_locations.end()) {
        logger.msg(DEBUG, "Locations of dataset %s are cached", dataset);
        sites = dq2_cache.dataset_locations[dataset];
        return DataStatus::Success;
      }
    }
    std::string duid;

    if (dq2_cache.dataset_duid.find(dataset) == dq2_cache.dataset_duid.end()) {

      std::string path("/dq2/ws_repository/rpc?operation=queryDatasetByName&dsn="+dataset+"&API=0_3_0&appid=arc");
      std::string content;
      DataStatus res = queryDQ2(content, "GET", path);
      if (!res) return res;

      cJSON *root = cJSON_Parse(content.c_str());
      if (!root) {
        logger.msg(ERROR, "Failed to parse DQ2 response: %s", content);
        return DataStatus(DataStatus::ReadResolveError, "Failed to parse DQ2 response");
      }
      cJSON *datasetinfo = cJSON_GetObjectItem(root, dataset.c_str());
      if (!datasetinfo) {
        logger.msg(ERROR, "No such dataset: %s", dataset);
        return DataStatus(DataStatus::ReadResolveError, ENOENT, "No such dataset");
      }
      cJSON *duidinfo = cJSON_GetObjectItem(datasetinfo, "duid");
      if (!duidinfo) {
        logger.msg(ERROR, "Malformed DQ2 response: %s", content);
        return DataStatus(DataStatus::ReadResolveError, "DQ2 returned a malformed response");
      }
      duid = duidinfo->valuestring;
      cJSON_Delete(root);
      dq2_cache.dataset_duid[dataset] = duid;
    } else {
      duid = dq2_cache.dataset_duid[dataset];
    }
    logger.msg(DEBUG, "Dataset %s: DUID %s", dataset, duid);


    std::string path("/dq2/ws_location/rpc");
    std::string post_data("operation=listDatasetReplicas&API=0_3_0&appid=arc&duid="+duid);
    std::string content;
    DataStatus res = queryDQ2(content, "POST", path, post_data);

    cJSON *root = cJSON_Parse(content.c_str());
    if (!root) {
      logger.msg(ERROR, "Failed to parse DQ2 response: %s", content);
      return DataStatus(DataStatus::ReadResolveError, "Failed to parse DQ2 response");
    }

    cJSON *subitem=root->child;
    while (subitem) {
      sites.push_back(subitem->string);
      logger.msg(DEBUG, "Location: %s", sites.back());
      subitem = subitem->next;
    }
    cJSON_Delete(root);


    Glib::Mutex::Lock l(dq2_cache_lock);
    dq2_cache.dataset_locations[dataset] = sites;
    return DataStatus::Success;
  }
