endl(CVC3::ExprStream& os) {
    if(os.d_indent) {

      int n(os.d_indentStack.size()? os.d_indentStack.back() : 0);

      string spaces(n, ' ');
      (*os.d_os) << endl << spaces;
      os.d_col = n;
    } else {
      (*os.d_os) << endl;
      os.d_col = 0;
    }
    os.d_beginningOfLine = true;
    return os;
  }
