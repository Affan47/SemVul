dropTriviallyDeadConstantArrays() {
  bool Changed;
  do {
    Changed = false;

    for (auto I = ArrayConstants.map_begin(), E = ArrayConstants.map_end();
         I != E; ) {
      auto *C = I->first;
      I++;
      if (C->use_empty()) {
        Changed = true;
        C->destroyConstant();
      }
    }

  } while (Changed);
}
