set_width(unsigned w, bool)
{
      bool flag = true;
      switch (op_) {

	  case 'l':
	  case 'r':

	    assert(0);
	    break;


	  default:
	    expr_width(left_->expr_width() > right_->expr_width()
			  ? left_->expr_width() : right_->expr_width());
	    cerr << "NetEBinary::set_width(): Using default for " <<
		  op_ << "." << endl;
	    flag = false;

	  case '%':
	  case '/':
	    flag = left_->set_width(w) && flag;
	    flag = right_->set_width(w) && flag;
	    expr_width(w);
	    break;
      }
      return flag;
}
