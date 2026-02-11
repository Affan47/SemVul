addEdge(uint64_t first_id, uint64_t second_id) {

    if ( this->edgeExists(first_id, second_id)) {
      OCTOMAP_ERROR("addEdge:: Edge exists!\n");
      return NULL;
    }

    ScanNode* first = getNodeByID(first_id);
    ScanNode* second = getNodeByID(second_id);

    if ((first != 0) && (second != 0)) {
      pose6d constr = first->pose.inv() * second->pose;
      return this->addEdge(first, second, constr);
    }
    else {
      OCTOMAP_ERROR("addEdge:: one or both scans invalid.\n");
      return NULL;
    }
  }
