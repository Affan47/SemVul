NegativeZeroTest(Register result,
                                      Register op,
                                      Label* then_label) {
  NearLabel ok;
  testl(result, result);
  j(not_zero, &ok);
  testl(op, op);
  j(sign, then_label);
  bind(&ok);
}
