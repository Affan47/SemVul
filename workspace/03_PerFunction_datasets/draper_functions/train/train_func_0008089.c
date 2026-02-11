renderLinenoCatchup(render_guts_t* guts, rope_t &rope) const {
  if (!this->lineno() || guts->lineno >= this->lineno()) {
    return false;
  }
  rope += rope_t(this->lineno() - guts->lineno, '\n');
  guts->lineno = this->lineno();
  return true;
}
