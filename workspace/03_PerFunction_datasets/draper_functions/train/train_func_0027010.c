state_rule_lookahead_tokens_print_xml (state *s, rule *r,
                                       FILE *out, int level)
{

  reductions *reds = s->reductions;
  int red = state_reduction_find (s, r);


  if (reds->lookahead_tokens && red != -1)
    {
      bitset_iterator biter;
      int k;
      xml_puts (out, level, "<lookaheads>");
      BITSET_FOR_EACH (biter, reds->lookahead_tokens[red], k, 0)
        {
          xml_printf (out, level + 1, "<symbol>%s</symbol>",
                      xml_escape (symbols[k]->tag));
        }
      xml_puts (out, level, "</lookaheads>");
    }
}
