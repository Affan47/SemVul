render(render_guts_t* guts, int indentation) const {
  return rope_t(this->_childNodes.front()->render(guts, indentation)) + (guts->pretty ? ": " : ":") +
    this->_childNodes.back()->render(guts, indentation);
}
