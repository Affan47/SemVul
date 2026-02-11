CollectExternalNamespaces(xmlNodePtr node_, std::map<xmlNsPtr,xmlNsPtr>& extns) {
    if (node_ == NULL) return;
    if (node_->type != XML_ELEMENT_NODE) return;
    std::map<xmlNsPtr,xmlNsPtr> localns;
    xmlNodePtr node = node_;
    for(;;) {
      if(node->type == XML_ELEMENT_NODE) {
        for(xmlNsPtr ns = node->nsDef; ns ; ns = ns->next) {
          localns[ns] = NULL;
        }

        if(node->ns) {
          if(localns.find(node->ns) == localns.end()) extns[node->ns] = NULL;
        }
        for(xmlAttrPtr attr = node->properties; attr ; attr = attr->next) {
          if(attr->ns) {
            if(localns.find(attr->ns) == localns.end()) extns[attr->ns] = NULL;
          }
        }
      }

      if(node->children) {
        node = node->children;
        continue;
      }

      if(node->next) {
        node = node->next;
        continue;
      }

      for(;;) {
        if((node == node_) || (!node)) return;
        node = node->parent;
        if((node == node_) || (!node)) return;
        if(node->next) {
          node = node->next;
          break;
        }
      }
    }
  }
