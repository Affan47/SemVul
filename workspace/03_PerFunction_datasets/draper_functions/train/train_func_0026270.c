real_compare (icode, op0, op1)
     int icode;
     const REAL_VALUE_TYPE *op0, *op1;
{
  enum tree_code code = icode;

  switch (code)
    {
    case LT_EXPR:
      return do_compare (op0, op1, 1) < 0;
    case LE_EXPR:
      return do_compare (op0, op1, 1) <= 0;
    case GT_EXPR:
      return do_compare (op0, op1, -1) > 0;
    case GE_EXPR:
      return do_compare (op0, op1, -1) >= 0;
    case EQ_EXPR:
      return do_compare (op0, op1, -1) == 0;
    case NE_EXPR:
      return do_compare (op0, op1, -1) != 0;
    case UNORDERED_EXPR:
      return op0->class == rvc_nan || op1->class == rvc_nan;
    case ORDERED_EXPR:
      return op0->class != rvc_nan && op1->class != rvc_nan;
    case UNLT_EXPR:
      return do_compare (op0, op1, -1) < 0;
    case UNLE_EXPR:
      return do_compare (op0, op1, -1) <= 0;
    case UNGT_EXPR:
      return do_compare (op0, op1, 1) > 0;
    case UNGE_EXPR:
      return do_compare (op0, op1, 1) >= 0;
    case UNEQ_EXPR:
      return do_compare (op0, op1, 0) == 0;

    default:
      abort ();
    }
}
