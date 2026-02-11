Initialize() {
  if (real_climit_ == kIllegalLimit) {


    uintptr_t limit = reinterpret_cast<uintptr_t>(&limit) - kLimitSize;
    ASSERT(reinterpret_cast<uintptr_t>(&limit) > kLimitSize);
    real_jslimit_ = SimulatorStack::JsLimitFromCLimit(limit);
    jslimit_ = SimulatorStack::JsLimitFromCLimit(limit);
    real_climit_ = limit;
    climit_ = limit;
    Heap::SetStackLimits();
  }
  nesting_ = 0;
  postpone_interrupts_nesting_ = 0;
  interrupt_flags_ = 0;
}
