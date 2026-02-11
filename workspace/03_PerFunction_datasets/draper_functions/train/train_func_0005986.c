Age() {

  for (int i = generations_ - 1; i > 0; i--) {
    tables_[i] = tables_[i - 1];
  }


  tables_[0] = isolate()->heap()->undefined_value();
}
