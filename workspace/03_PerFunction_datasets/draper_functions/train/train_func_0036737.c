sb_ivy_write_just(String_buf sb, Ivyjust j, I3list map)
{
  if (j->type == INPUT_JUST) {
    sb_append(sb, "(input)");
  }
  else if (j->type == PROPOSITIONAL_JUST) {
    sb_append(sb, "(propositional ");
    sb_append_id(sb, j->parent1, map);
    sb_append(sb, ")");
  }
  else if (j->type == NEW_SYMBOL_JUST) {
    sb_append(sb, "(new_symbol ");
    sb_append_id(sb, j->parent1, map);
    sb_append(sb, ")");
  }
  else if (j->type == FLIP_JUST) {
    sb_append(sb, "(flip ");
    sb_append_id(sb, j->parent1, map);
    sb_append(sb, " ");
    sb_ivy_write_position(sb, j->pos1);
    sb_append(sb, ")");
  }
  else if (j->type == INSTANCE_JUST) {
    sb_append(sb, "(instantiate ");
    sb_append_id(sb, j->parent1, map);
    sb_append(sb, " ");
    sb_ivy_write_pairs(sb, j->pairs);
    sb_append(sb, ")");
  }
  else if (j->type == BINARY_RES_JUST ||
	   j->type == PARA_JUST) {
    if (j->type == BINARY_RES_JUST)
      sb_append(sb, "(resolve ");
    else
      sb_append(sb, "(paramod ");
    sb_append_id(sb, j->parent1, map);
    sb_append(sb, " ");
    sb_ivy_write_position(sb, j->pos1);
    sb_append(sb, " ");
    sb_append_id(sb, j->parent2, map);
    sb_append(sb, " ");
    sb_ivy_write_position(sb, j->pos2);
    sb_append(sb, ")");
  }
  else
    fatal_error("sb_ivy_write_just, bad ivy justification");
}
