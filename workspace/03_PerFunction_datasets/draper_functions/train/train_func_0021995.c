evalAsFixed() {
  IDL_Fixed *a, *b, *r;
  a = a_->evalAsFixed(); b = b_->evalAsFixed();
  try {
    r = new IDL_Fixed(*a / *b);
  }
  catch (IDL_Fixed::Overflow&) {
    IdlError(file(), line(), "Sub-expression overflows fixed digits");
    r = new IDL_Fixed("1");
  }
  catch (IDL_Fixed::DivideByZero&) {
    IdlError(file(), line(), "Divide by zero");
    r = new IDL_Fixed("1");
  }
  delete a; delete b;
  return r;
}
