endScope()
{
  if (current_->parent_)
    delete current_;
  else
    IdlWarning(currentFile, yylineno,
	       "Confused by pre-processor line directives");
}
