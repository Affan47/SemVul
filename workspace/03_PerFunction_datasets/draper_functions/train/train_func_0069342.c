operator<<(ExprStream& os, const string& s) {

    int oldCol(os.d_col);

    os.d_col += s.size();
    if(os.d_indent) {

      int n(os.d_indentStack.size()? os.d_indentStack.back() : 0);

      if(2*os.d_col > os.d_lineWidth && 4*(os.d_col - n) > os.d_lineWidth
	 && 6*(oldCol - n) > os.d_lineWidth) {
	os << endl;

	os.d_col += s.size();
      }
    }
    *os.d_os << s;
    os.d_beginningOfLine = false;
    return os;
  }
