RemoveDeadNode(SDNode *N, DAGUpdateListener *UpdateListener){
  SmallVector<SDNode*, 16> DeadNodes(1, N);
  RemoveDeadNodes(DeadNodes, UpdateListener);
}
