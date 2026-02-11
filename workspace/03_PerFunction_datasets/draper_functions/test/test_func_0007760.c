release(AREXClient* client) {
    if(!client) return;
    if(!*client) return;

    clients_.insert(std::pair<URL, AREXClient*>(client->url(),client));
  }
