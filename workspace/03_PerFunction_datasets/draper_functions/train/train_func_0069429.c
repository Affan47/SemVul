inspectPath(void) {
    QMutexLocker locker(&mutex);
    setCurrentNode(root);
    if (currentNode->isOnPath()) {
      inspectCurrentNode();
      int nextAlt = currentNode->getPathAlternative(*na);
      while (nextAlt >= 0) {
        setCurrentNode(currentNode->getChild(*na,nextAlt));
        inspectCurrentNode();
        nextAlt = currentNode->getPathAlternative(*na);
      }
    }
    update();
  }
