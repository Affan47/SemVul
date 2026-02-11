copy(const BrokerPlugin* p, bool keep_ownerskip) {
    if (p) {
      BrokerPlugin* bp = new BrokerPlugin(*p);
      if (bp) {
        if (keep_ownerskip) {
          plugins.push_back(bp);
        };
        return bp;
      };
    };
    return NULL;
  }
