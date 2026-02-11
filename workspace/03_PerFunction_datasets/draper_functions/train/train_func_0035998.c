itv_eval_ap_texpr0_node(itv_internal_t* intern,
			ap_texpr0_node_t* n,
			itv_t res, itv_t arg1, itv_t arg2)
{
  switch (n->op) {
  case AP_TEXPR_NEG:
    itv_neg(res, arg1);
    return;
  case AP_TEXPR_CAST:
    itv_set(res, arg1);
    break;
  case AP_TEXPR_SQRT:
    itv_sqrt(intern, res, arg1);
    break;
  case AP_TEXPR_ADD:
    itv_add(res, arg1, arg2);
    break;
  case AP_TEXPR_SUB:
    itv_sub(res, arg1, arg2);
    break;
  case AP_TEXPR_MUL:
    itv_mul(intern, res, arg1, arg2);
    break;
  case AP_TEXPR_DIV:
    itv_div(intern, res, arg1, arg2);
    break;
  case AP_TEXPR_MOD:
    itv_mod(intern, res, arg1, arg2, n->type==AP_RTYPE_INT);
    return;
  default:
    assert(0);
  }
  itv_round(res,res,n->type,n->dir);
}
