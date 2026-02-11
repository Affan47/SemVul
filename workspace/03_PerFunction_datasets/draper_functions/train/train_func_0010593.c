EliminateUnreachablePhis() {
  HPhase phase("Unreachable phi elimination", this);


  ZoneList<HPhi*> phi_list(blocks_.length());
  ZoneList<HPhi*> worklist(blocks_.length());
  for (int i = 0; i < blocks_.length(); ++i) {
    for (int j = 0; j < blocks_[i]->phis()->length(); j++) {
      HPhi* phi = blocks_[i]->phis()->at(j);
      phi_list.Add(phi);


      if (phi->HasRealUses() || phi->IsReceiver())  {
        phi->set_is_live(true);
        worklist.Add(phi);
      }
    }
  }


  while (!worklist.is_empty()) {
    HPhi* phi = worklist.RemoveLast();
    for (int i = 0; i < phi->OperandCount(); i++) {
      HValue* operand = phi->OperandAt(i);
      if (operand->IsPhi() && !HPhi::cast(operand)->is_live()) {
        HPhi::cast(operand)->set_is_live(true);
        worklist.Add(HPhi::cast(operand));
      }
    }
  }


  for (int i = 0; i < phi_list.length(); i++) {
    HPhi* phi = phi_list[i];
    if (!phi->is_live()) {
      HBasicBlock* block = phi->block();
      block->RemovePhi(phi);
      block->RecordDeletedPhi(phi->merged_index());
    }
  }
}
