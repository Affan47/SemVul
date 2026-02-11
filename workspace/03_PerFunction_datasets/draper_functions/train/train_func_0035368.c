getAsString() const {
   return TI->getAsString() + "{" + utostr(Bit) + "}";
}
