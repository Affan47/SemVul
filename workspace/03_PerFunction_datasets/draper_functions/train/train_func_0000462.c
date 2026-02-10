send_ruleset_governments(struct conn_list *dest)
{
  struct packet_ruleset_government gov;
  struct packet_ruleset_government_ruler_title title;
  int j;

  governments_iterate(g) {

    gov.id = government_number(g);

    j = 0;
    requirement_vector_iterate(&g->reqs, preq) {
      gov.reqs[j++] = *preq;
    } requirement_vector_iterate_end;
    gov.reqs_count = j;

    sz_strlcpy(gov.name, untranslated_name(&g->name));
    sz_strlcpy(gov.rule_name, rule_name(&g->name));
    sz_strlcpy(gov.graphic_str, g->graphic_str);
    sz_strlcpy(gov.graphic_alt, g->graphic_alt);
    PACKET_STRVEC_COMPUTE(gov.helptext, g->helptext);

    lsend_packet_ruleset_government(dest, &gov);


    ruler_titles_iterate(government_ruler_titles(g), pruler_title) {
      const struct nation_type *pnation = ruler_title_nation(pruler_title);

      title.gov = government_number(g);
      title.nation = (NULL != pnation ? nation_number(pnation) : -1);
      sz_strlcpy(title.male_title,
                 ruler_title_male_untranslated_name(pruler_title));
      sz_strlcpy(title.female_title,
                 ruler_title_female_untranslated_name(pruler_title));
      lsend_packet_ruleset_government_ruler_title(dest, &title);
    } ruler_titles_iterate_end;
  } governments_iterate_end;
}
