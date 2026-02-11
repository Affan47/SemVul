NumberFromDouble(double value, PretenureFlag pretenure) {


  static const DoubleRepresentation minus_zero(-0.0);

  DoubleRepresentation rep(value);
  if (rep.bits == minus_zero.bits) {
    return AllocateHeapNumber(-0.0, pretenure);
  }

  int int_value = FastD2I(value);
  if (value == int_value && Smi::IsValid(int_value)) {
    return Smi::FromInt(int_value);
  }


  return AllocateHeapNumber(value, pretenure);
}
