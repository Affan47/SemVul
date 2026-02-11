endFile()
{
  if (!current_->isfile()) {
    IdlWarning(currentFile, yylineno,
	       "File ended inside a declaration. "
	       "Repository identifiers may be incorrect");
  }
  if (current_->parent_)
    delete current_;
  else
    IdlWarning(currentFile, yylineno,
	       "Confused by pre-processor line directives");
}
