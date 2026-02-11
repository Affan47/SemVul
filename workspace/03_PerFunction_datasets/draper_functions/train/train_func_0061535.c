BuildSwitchCompare(HSubgraph* subgraph,
                                            HValue* switch_value,
                                            CaseClause* clause) {
  AddToSubgraph(subgraph, clause->label());
  if (HasStackOverflow()) return NULL;
  HValue* clause_value = subgraph->exit_block()->last_environment()->Pop();
  HCompare* compare = new HCompare(switch_value,
                                   clause_value,
                                   Token::EQ_STRICT);
  compare->SetInputRepresentation(Representation::Integer32());
  subgraph->exit_block()->AddInstruction(compare);
  return compare;
}
