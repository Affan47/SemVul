_vbuild_rule(parse_tree_branch_t *branch)
{
  parse_rule_t *rule;
  int tokens = 0, tokenpos = 0, i;

  while (tokenpos < 10 && branch->data[tokenpos]) {
    int type = branch->data[tokenpos];
    tokenpos += 2;

    if ((type == VOCAB_TREE_NODE_COMPARE_TYPE)
	|| (type == VOCAB_TREE_NODE_COMPARE_GROUP)
	|| (type == VOCAB_TREE_NODE_FORCE_STORAGE))
      ++tokens;
    else if (type > VOCAB_TREE_NODE_LAST_WORD_STORAGE)
      tokens += 5;
    else return NULL;
  }

  rule = (parse_rule_t*)sci_malloc(sizeof(int) * (4 + tokens));

  ++_allocd_rules;
  rule->id = branch->id;
  rule->specials_nr = tokenpos >> 1;
  rule->length = tokens;
  rule->first_special = 0;

  tokens = 0;
  for (i = 0; i < tokenpos; i += 2) {
    int type = branch->data[i];
    int value = branch->data[i + 1];

    if (type == VOCAB_TREE_NODE_COMPARE_TYPE)
      rule->data[tokens++] = value | TOKEN_TERMINAL_CLASS;
    else if (type == VOCAB_TREE_NODE_COMPARE_GROUP)
      rule->data[tokens++] = value | TOKEN_TERMINAL_GROUP;
    else if (type == VOCAB_TREE_NODE_FORCE_STORAGE)
      rule->data[tokens++] = value | TOKEN_STUFFING_WORD;
    else {
      rule->data[tokens++] = TOKEN_OPAREN;
      rule->data[tokens++] = type | TOKEN_STUFFING_WORD;
      rule->data[tokens++] = value | TOKEN_STUFFING_WORD;

      if (i == 0)
	rule->first_special = tokens;

      rule->data[tokens++] = value;
      rule->data[tokens++] = TOKEN_CPAREN;
    }
  }

  return rule;
}
