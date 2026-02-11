getRecurrenceIdentity(RecurrenceKind K,
                                                      Type *Tp) {
  switch (K) {
  case RK_IntegerXor:
  case RK_IntegerAdd:
  case RK_IntegerOr:

    return ConstantInt::get(Tp, 0);
  case RK_IntegerMult:

    return ConstantInt::get(Tp, 1);
  case RK_IntegerAnd:

    return ConstantInt::get(Tp, -1, true);
  case RK_FloatMult:

    return ConstantFP::get(Tp, 1.0L);
  case RK_FloatAdd:

    return ConstantFP::get(Tp, 0.0L);
  default:
    llvm_unreachable("Unknown recurrence kind");
  }
}
