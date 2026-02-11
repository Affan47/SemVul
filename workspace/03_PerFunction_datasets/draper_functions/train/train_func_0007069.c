rows(int val) {
  Fl_Table::rows(val);
  while ( val > (int)_rowselect.size() ) { _rowselect.push_back(0); }
  while ( val < (int)_rowselect.size() ) { _rowselect.pop_back(); }
}
