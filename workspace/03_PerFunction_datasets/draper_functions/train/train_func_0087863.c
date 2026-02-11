VisitCountOperation(CountOperation* node) {

  node->expression()->set_no_negative_zero(node->is_prefix() ?
                                           true :
                                           node->no_negative_zero());
  node->type()->SetAsLikelySmiIfUnknown();
  node->expression()->type()->SetAsLikelySmiIfUnknown();
  Visit(node->expression());
}
