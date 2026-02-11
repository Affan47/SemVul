precedence(ExprNodeOutputType output_type, const temporary_terms_t &temporary_terms) const
{
  temporary_terms_t::const_iterator it = temporary_terms.find(const_cast<BinaryOpNode *>(this));

  if (it != temporary_terms.end())
    return 100;

  switch (op_code)
    {
    case oEqual:
      return 0;
    case oEqualEqual:
    case oDifferent:
      return 1;
    case oLessEqual:
    case oGreaterEqual:
    case oLess:
    case oGreater:
      return 2;
    case oPlus:
    case oMinus:
      return 3;
    case oTimes:
    case oDivide:
      return 4;
    case oPower:
    case oPowerDeriv:
      if (IS_C(output_type))

        return 100;
      else
        return 5;
    case oMin:
    case oMax:
      return 100;
    }

  exit(EXIT_FAILURE);
}
