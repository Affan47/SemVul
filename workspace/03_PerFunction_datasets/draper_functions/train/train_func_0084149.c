createTree(const std::string class_name, double res){
    std::map<std::string, AbstractOcTree*>::iterator it = classIDMapping().find(class_name);
    if (it == classIDMapping().end()){
      OCTOMAP_ERROR("Could not create octree of type %s, not in store in classIDMapping\n", class_name.c_str());
      return NULL;
    } else {
      AbstractOcTree* tree = it->second->create();

      tree->setResolution(res);
      return tree;
    }
  }
