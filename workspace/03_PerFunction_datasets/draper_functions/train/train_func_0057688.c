combineWeightsByHashing(WeightList &Weights) {

  typedef DenseMap<BlockNode::IndexType, Weight> HashTable;
  HashTable Combined(NextPowerOf2(2 * Weights.size()));
  for (const Weight &W : Weights)
    combineWeight(Combined[W.TargetNode.Index], W);


  if (Weights.size() == Combined.size())
    return;


  Weights.clear();
  Weights.reserve(Combined.size());
  for (const auto &I : Combined)
    Weights.push_back(I.second);
}
