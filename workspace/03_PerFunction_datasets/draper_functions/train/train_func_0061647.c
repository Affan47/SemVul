getToken(int32_t index) {
  QueryToken* t = lookingAhead ? jj_scanpos : token;
  for (int32_t i = 0; i < index; i++) {
    if (t->next != NULL) t = t->next;
    else t = t->next = token_source->getNextToken();
  }
  return t;
}
