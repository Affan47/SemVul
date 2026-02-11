updateNode(const OcTreeKey& k) {

    CountingOcTreeNode* curNode (root);
    curNode->increaseCount();


    for (int i=(tree_depth-1); i>=0; i--) {

      unsigned int pos = computeChildIdx(k, i);


      if (!curNode->childExists(pos)) {
        curNode->createChild(pos);
        tree_size++;
      }

      curNode = static_cast<CountingOcTreeNode*> (curNode->getChild(pos));
      curNode->increaseCount();
    }

    return curNode;
  }
