copy_justification(Just j)
{
  if (j == NULL)
    return NULL;
  else {
    Just j2 = get_just();
    j2->type = j->type;
    j2->next = copy_justification(j->next);
    switch (j->type) {
    case INPUT_JUST:
    case GOAL_JUST:
      break;
    case DENY_JUST:
    case CLAUSIFY_JUST:
    case COPY_JUST:
    case PROPOSITIONAL_JUST:
    case NEW_SYMBOL_JUST:
    case BACK_DEMOD_JUST:
    case BACK_UNIT_DEL_JUST:
    case FLIP_JUST:
    case XX_JUST:
    case MERGE_JUST:
    case EVAL_JUST:
      j2->u.id = j->u.id;
      break;
    case EXPAND_DEF_JUST:
    case BINARY_RES_JUST:
    case HYPER_RES_JUST:
    case UR_RES_JUST:
    case UNIT_DEL_JUST:
    case FACTOR_JUST:
    case XXRES_JUST:
      j2->u.lst = copy_ilist(j->u.lst);
      break;
    case DEMOD_JUST:
      j2->u.demod = copy_i3list(j->u.demod);
      break;
    case PARA_JUST:
    case PARA_FX_JUST:
    case PARA_IX_JUST:
    case PARA_FX_IX_JUST:
      j2->u.para = get_parajust();
      j2->u.para->from_id = j->u.para->from_id;
      j2->u.para->into_id = j->u.para->into_id;
      j2->u.para->from_pos = copy_ilist(j->u.para->from_pos);
      j2->u.para->into_pos = copy_ilist(j->u.para->into_pos);
      break;
    case INSTANCE_JUST:
      j2->u.instance = get_instancejust();
      j2->u.instance->parent_id = j->u.instance->parent_id;
      j2->u.instance->pairs = copy_plist_of_terms(j->u.instance->pairs);
      break;
    case IVY_JUST:
      j2->u.ivy = get_ivyjust();
      j2->u.ivy->type = j->u.ivy->type;
      j2->u.ivy->parent1 = j->u.ivy->parent1;
      j2->u.ivy->parent2 = j->u.ivy->parent2;
      j2->u.ivy->pos1 = copy_ilist(j->u.ivy->pos1);
      j2->u.ivy->pos2 = copy_ilist(j->u.ivy->pos2);
      j2->u.ivy->pairs = copy_plist_of_terms(j->u.ivy->pairs);
      break;
    default: fatal_error("copy_justification: unknown type");
    }
    return j2;
  }
}
