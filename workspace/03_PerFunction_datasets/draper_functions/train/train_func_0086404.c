nodes_identical_1 (struct decision_test *d1, struct decision_test *d2)
{
  switch (d1->type)
    {
    case DT_num_insns:
      return d1->u.num_insns == d2->u.num_insns;

    case DT_mode:
      return d1->u.mode == d2->u.mode;

    case DT_code:
      return d1->u.code == d2->u.code;

    case DT_pred:
      return (d1->u.pred.mode == d2->u.pred.mode
	      && strcmp (d1->u.pred.name, d2->u.pred.name) == 0);

    case DT_c_test:
      return strcmp (d1->u.c_test, d2->u.c_test) == 0;

    case DT_veclen:
    case DT_veclen_ge:
      return d1->u.veclen == d2->u.veclen;

    case DT_dup:
      return d1->u.dup == d2->u.dup;

    case DT_elt_zero_int:
    case DT_elt_one_int:
    case DT_elt_zero_wide:
    case DT_elt_zero_wide_safe:
      return d1->u.intval == d2->u.intval;

    case DT_accept_op:
      return d1->u.opno == d2->u.opno;

    case DT_accept_insn:

      return 1;

    default:
      gcc_unreachable ();
    }
}
