nextSection(
    const string& sectName) {

  nextSection();


  while (!p->text.empty()) {
    if (isSection(sectName)) return *this;

    nextSection();
  }


  return *this;
}
