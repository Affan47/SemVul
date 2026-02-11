attr_alt_union (rtx s1, rtx s2)
{
  rtx result = rtx_alloc (EQ_ATTR_ALT);

  switch ((XINT (s1, 1) << 1) | XINT (s2, 1))
    {
    case (0 << 1) | 0:
      XINT (result, 0) = XINT (s1, 0) | XINT (s2, 0);
      break;
    case (0 << 1) | 1:
      XINT (result, 0) = XINT (s2, 0) & ~XINT (s1, 0);
      break;
    case (1 << 1) | 0:
      XINT (result, 0) = XINT (s1, 0) & ~XINT (s2, 0);
      break;
    case (1 << 1) | 1:
      XINT (result, 0) = XINT (s1, 0) & XINT (s2, 0);
      break;
    default:
      gcc_unreachable ();
    }

  XINT (result, 1) = XINT (s1, 1) | XINT (s2, 1);
  return result;
}
