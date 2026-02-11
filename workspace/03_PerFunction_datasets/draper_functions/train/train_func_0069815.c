bnr_finalize(BNR_CTX *BTX) {
  int BNR_SIZE = BTX->window_size;
  struct bnr_list_node * previous_bnr_tokens[BNR_SIZE];
  float previous_bnr_probs[BNR_SIZE];
  struct bnr_list_node *node_list;
  struct bnr_list_c c_list;
  char bnr_token[64];
  int i, interesting;

  for(i=0;i<BNR_SIZE;i++) {
    previous_bnr_probs[i] = 0.00000;
    previous_bnr_tokens[i] = NULL;
  }

  node_list = c_bnr_list_first(BTX->stream, &c_list);
  while(node_list != NULL) {
    float pattern_value;

    for(i=1;i<BNR_SIZE;i++) {
      previous_bnr_probs[i-1] = previous_bnr_probs[i];
      previous_bnr_tokens[i-1] = previous_bnr_tokens[i];
    }

    previous_bnr_probs[BNR_SIZE-1] = _bnr_round(node_list->value);
    previous_bnr_tokens[BNR_SIZE-1] = node_list;

    sprintf(bnr_token, "bnr.%c|", BTX->identifier);
    for(i=0;i<BNR_SIZE;i++) {
      char x[6];
      snprintf(x, 6, "%01.2f_", previous_bnr_probs[i]);
      strcat(bnr_token, x);
    }


    pattern_value = bnr_hash_value(BTX->patterns, bnr_token);
    interesting = (fabs(0.5-pattern_value) > BTX->ex_radius);

    if (interesting) {

#ifdef LIBBNR_VERBOSE_DEBUG
      fprintf(stderr, "Analyzing Pattern '%s' P-Value: %1.5f\n", bnr_token,
        pattern_value);
#endif


      for(i=0;i<BNR_SIZE;i++) {
        if (previous_bnr_tokens[i]) {


          if (fabs(previous_bnr_tokens[i]->value - pattern_value) > BTX->in_radius)
          {
#ifdef LIBBNR_VERBOSE_DEBUG
            fprintf(stderr, "\tEliminating '%s' P-Value: %1.5f\n",
              (const char *) previous_bnr_tokens[i]->ptr,
              previous_bnr_tokens[i]->value);
#endif
            BTX->eliminations++;
            previous_bnr_tokens[i]->eliminated = 1;
          }
        }
      }
    }

    node_list = c_bnr_list_next(BTX->stream, &c_list);
  }

  return 0;
}
