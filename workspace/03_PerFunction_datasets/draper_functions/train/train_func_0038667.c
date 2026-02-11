ParseStatement(ZoneStringList* labels, bool* ok) {


  int statement_pos = scanner().peek_location().beg_pos;
  Statement* stmt = NULL;
  switch (peek()) {
    case Token::LBRACE:
      return ParseBlock(labels, ok);

    case Token::CONST:
    case Token::VAR:
      stmt = ParseVariableStatement(kStatement, ok);
      break;

    case Token::SEMICOLON:
      Next();
      return EmptyStatement();

    case Token::IF:
      stmt = ParseIfStatement(labels, ok);
      break;

    case Token::DO:
      stmt = ParseDoWhileStatement(labels, ok);
      break;

    case Token::WHILE:
      stmt = ParseWhileStatement(labels, ok);
      break;

    case Token::FOR:
      stmt = ParseForStatement(labels, ok);
      break;

    case Token::CONTINUE:
      stmt = ParseContinueStatement(ok);
      break;

    case Token::BREAK:
      stmt = ParseBreakStatement(labels, ok);
      break;

    case Token::RETURN:
      stmt = ParseReturnStatement(ok);
      break;

    case Token::WITH:
      stmt = ParseWithStatement(labels, ok);
      break;

    case Token::SWITCH:
      stmt = ParseSwitchStatement(labels, ok);
      break;

    case Token::THROW:
      stmt = ParseThrowStatement(ok);
      break;

    case Token::TRY: {


      Block* result = new(zone()) Block(isolate(), labels, 1, false);
      Target target(&this->target_stack_, result);
      TryStatement* statement = ParseTryStatement(CHECK_OK);
      if (statement) {
        statement->set_statement_pos(statement_pos);
      }
      if (result) result->AddStatement(statement);
      return result;
    }

    case Token::FUNCTION: {


      if (top_scope_->is_strict_mode()) {
        ReportMessageAt(scanner().peek_location(), "strict_function",
                        Vector<const char*>::empty());
        *ok = false;
        return NULL;
      }
      return ParseFunctionDeclaration(ok);
    }

    case Token::DEBUGGER:
      stmt = ParseDebuggerStatement(ok);
      break;

    default:
      stmt = ParseExpressionOrLabelledStatement(labels, ok);
  }


  if (stmt != NULL) stmt->set_statement_pos(statement_pos);
  return stmt;
}
