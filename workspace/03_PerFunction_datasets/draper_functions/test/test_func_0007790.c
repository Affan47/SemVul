DoMathFloor(LUnaryMathOperation* instr) {
  XMMRegister xmm_scratch = xmm0;
  Register output_reg = ToRegister(instr->result());
  XMMRegister input_reg = ToDoubleRegister(instr->InputAt(0));
  __ xorpd(xmm_scratch, xmm_scratch);
  __ ucomisd(input_reg, xmm_scratch);

  if (instr->hydrogen()->CheckFlag(HValue::kBailoutOnMinusZero)) {
    DeoptimizeIf(below_equal, instr->environment());
  } else {
    DeoptimizeIf(below, instr->environment());
  }


  __ cvttsd2si(output_reg, input_reg);


  __ cmpl(output_reg, Immediate(0x80000000));
  DeoptimizeIf(equal, instr->environment());
}
