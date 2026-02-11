ParseThrowStatement(bool* ok) {


  Expect(i::Token::THROW, CHECK_OK);
  if (scanner_->has_line_terminator_before_next()) {
    i::JavaScriptScanner::Location pos = scanner_->location();
    ReportMessageAt(pos.beg_pos, pos.end_pos,
                    "newline_after_throw", NULL);
    *ok = false;
    return kUnknownStatement;
  }
  ParseExpression(true, CHECK_OK);
  ExpectSemicolon(CHECK_OK);

  return kUnknownStatement;
}
