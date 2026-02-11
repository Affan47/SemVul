BlockContinues(Assignment* assignment) {
    if ((assignment == NULL) || (first_in_block_ == NULL)) return false;
    if (assignment->op() != Token::ASSIGN) return false;
    return PropertyOfSameObject(first_in_block_->target(),
                                assignment->target());
  }
