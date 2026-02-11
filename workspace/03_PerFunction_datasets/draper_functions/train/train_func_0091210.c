addSuccessor(MachineBasicBlock *succ, uint32_t weight) {


  if (weight != 0 && Weights.empty())
    Weights.resize(Successors.size());

  if (weight != 0 || !Weights.empty())
    Weights.push_back(weight);

   Successors.push_back(succ);
   succ->addPredecessor(this);
 }
