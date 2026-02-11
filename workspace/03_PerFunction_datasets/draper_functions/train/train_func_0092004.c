MarkDeoptimizeOnUndefined() {
  HPhase phase("MarkDeoptimizeOnUndefined", this);


  for (int i = 0; i < phi_list()->length(); i++) {
    HPhi* phi = phi_list()->at(i);
    if (phi->representation().IsDouble()) {
      for (HUseIterator it(phi->uses()); !it.Done(); it.Advance()) {
        if (it.value()->CheckFlag(HValue::kDeoptimizeOnUndefined)) {
          RecursivelyMarkPhiDeoptimizeOnUndefined(phi);
          break;
        }
      }
    }
  }
}
