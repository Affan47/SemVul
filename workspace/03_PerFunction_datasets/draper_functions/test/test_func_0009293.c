setNonInheritedC(const Identifier *ident, ELObj *obj,
				    const Location &loc, Interpreter &interp)
{
  Char c;
  if (obj->charValue(c)) {
    type_ = new CharType(c);
    return;
  }
  double d;
  long n;
  int dim;
  switch (obj->quantityValue(n, d, dim)) {
  case longQuantity:
    if (dim == 1) {
      type_ = new LengthSpecType(n);
      return;
    }
    break;
  case doubleQuantity:
    if (dim == 1) {
      type_ = new LengthSpecType(long(d));
      return;
    }
    break;
  default:
    break;
  }
  static FOTBuilder::Symbol vals[] = {
    FOTBuilder::symbolBefore,
    FOTBuilder::symbolThrough,
    FOTBuilder::symbolAfter
  };
  FOTBuilder::Symbol sym;
  if (interp.convertEnumC(vals, SIZEOF(vals), obj, ident, loc, sym))
    type_ = new SymbolType(sym);
}
