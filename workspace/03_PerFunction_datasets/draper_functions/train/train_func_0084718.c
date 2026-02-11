checkType(const Expr& e)
{
  switch (e.getKind()) {
    case ARRAY: {
      if (e.arity() != 2) throw Exception
          ("ARRAY type should have two arguments");
      Type t1(e[0]);
      if (t1.isBool()) throw Exception
          ("Array index types must be non-Boolean");
      if (t1.isFunction()) throw Exception
          ("Array index types cannot be functions");
      Type t2(e[1]);
      if (t2.isBool()) throw Exception
          ("Array value types must be non-Boolean");
      if (t2.isFunction()) throw Exception
          ("Array value types cannot be functions");
      break;
    }
    default:
      DebugAssert(false, "Unexpected kind in TheoryArray::checkType"
                  +getEM()->getKindName(e.getKind()));
  }

}
