AddNonPhiUsesFrom(HPhi* other) {
  for (int i = 0; i < Representation::kNumRepresentations; i++) {
    indirect_uses_[i] += other->non_phi_uses_[i];
  }
}
