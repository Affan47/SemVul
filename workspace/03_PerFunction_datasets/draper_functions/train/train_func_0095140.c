render(render_guts_t* guts, int indentation) const {
  return rope_t("[") + this->renderImplodeChildren(guts, indentation, guts->pretty ? ", " : ",") + "]";
}
