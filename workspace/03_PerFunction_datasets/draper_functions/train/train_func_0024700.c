enter () {
  if (_intro_level == 0)
    _cpp = &(PreprocessorParser&)_parser->syntax ().provider ()->source ();
  _intro_level++;
}
