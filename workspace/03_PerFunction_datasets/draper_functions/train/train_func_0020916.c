StatementAsSimpleAssignment() {
  return (expression()->AsAssignment() != NULL &&
          !expression()->AsAssignment()->is_compound())
      ? expression()->AsAssignment()
      : NULL;
}
