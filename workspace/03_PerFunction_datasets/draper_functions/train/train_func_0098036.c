print_owner_ttl(struct query_node *qun, adns_answer *answer) {
  if (qun->pqfr.show_owner) print_withspace(owner_show(qun,answer));
  print_ttl(qun,answer);
}
