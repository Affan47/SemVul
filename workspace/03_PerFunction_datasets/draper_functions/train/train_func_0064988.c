ParseSourceElements(ZoneList<Statement*>* processor,
                                  int end_token,
                                  bool* ok) {


  TargetScope scope(&this->target_stack_);

  ASSERT(processor != NULL);
  InitializationBlockFinder block_finder;
  ThisNamedPropertyAssigmentFinder this_property_assignment_finder;
  bool directive_prologue = true;

  while (peek() != end_token) {
    if (directive_prologue && peek() != Token::STRING) {
      directive_prologue = false;
    }

    Scanner::Location token_loc = scanner().peek_location();

    Statement* stat;
    if (peek() == Token::FUNCTION) {


      stat = ParseFunctionDeclaration(CHECK_OK);
    } else {
      stat = ParseStatement(NULL, CHECK_OK);
    }

    if (stat == NULL || stat->IsEmpty()) {
      directive_prologue = false;
      continue;
    }

    if (directive_prologue) {

      ExpressionStatement *e_stat;
      Literal *literal;

      if ((e_stat = stat->AsExpressionStatement()) != NULL &&
          (literal = e_stat->expression()->AsLiteral()) != NULL &&
          literal->handle()->IsString()) {
        Handle<String> directive = Handle<String>::cast(literal->handle());


        if (!temp_scope_->StrictMode() &&
            directive->Equals(Heap::use_strict()) &&
            token_loc.end_pos - token_loc.beg_pos ==
              Heap::use_strict()->length() + 2) {
          temp_scope_->EnableStrictMode();

          directive_prologue = false;
        }
      } else {

        directive_prologue = false;
      }
    }


    if (top_scope_->is_global_scope()) {
      block_finder.Update(stat);
    }

    if (top_scope_->is_function_scope()) {
      this_property_assignment_finder.Update(top_scope_, stat);
    }
    processor->Add(stat);
  }


  if (top_scope_->is_function_scope()) {
    bool only_simple_this_property_assignments =
        this_property_assignment_finder.only_simple_this_property_assignments()
        && top_scope_->declarations()->length() == 0;
    if (only_simple_this_property_assignments) {
      temp_scope_->SetThisPropertyAssignmentInfo(
          only_simple_this_property_assignments,
          this_property_assignment_finder.GetThisPropertyAssignments());
    }
  }
  return 0;
}
