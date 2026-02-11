moveup_set_expr (av_set_t *avp, insn_t insn, bool inside_insn_group)
{
  av_set_iterator i;
  expr_t expr;

  FOR_EACH_EXPR_1 (expr, i, avp)
    {

      switch (moveup_expr_cached (expr, insn, inside_insn_group))
	{
	case MOVEUP_EXPR_SAME:
        case MOVEUP_EXPR_AS_RHS:
	  break;

	case MOVEUP_EXPR_NULL:
	  av_set_iter_remove (&i);
	  break;

	case MOVEUP_EXPR_CHANGED:
          expr = merge_with_other_exprs (avp, &i, expr);
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}
