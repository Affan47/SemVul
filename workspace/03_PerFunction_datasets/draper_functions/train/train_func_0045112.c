VisitAssertion(AssertionNode* that) {
  EnsureAnalyzed(that->on_success());
  AssertionNode::AssertionNodeType type = that->type();
  if (type == AssertionNode::AT_BOUNDARY ||
      type == AssertionNode::AT_NON_BOUNDARY) {


    ZoneList<CharacterRange>* following_chars = that->FirstCharacterSet();

    CharacterRange::Canonicalize(following_chars);

    SetRelation word_relation =
        CharacterRange::WordCharacterRelation(following_chars);
    if (word_relation.ContainedIn()) {

      type = (type == AssertionNode::AT_BOUNDARY) ?
                  AssertionNode::AFTER_NONWORD_CHARACTER :
                  AssertionNode::AFTER_WORD_CHARACTER;
      that->set_type(type);
    } else if (word_relation.Disjoint()) {

      type = (type == AssertionNode::AT_BOUNDARY) ?
                  AssertionNode::AFTER_WORD_CHARACTER :
                  AssertionNode::AFTER_NONWORD_CHARACTER;
      that->set_type(type);
    }
  }
}
