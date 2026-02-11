calculate_gate_and_lval_count_(unsigned&gate_count,
                                               unsigned&lval_count) const
{
      switch (type()) {
	  case BUF:
	  case NOT:
	    if (pin_count() > 2) gate_count = pin_count() - 1;
	    else gate_count = 1;
            lval_count = gate_count;
	    break;
	  case PULLDOWN:
	  case PULLUP:
	    gate_count = pin_count();
            lval_count = gate_count;
	    break;
	  case TRAN:
	  case RTRAN:
	  case TRANIF0:
	  case TRANIF1:
	  case RTRANIF0:
	  case RTRANIF1:
	    gate_count = 1;
            lval_count = 2;
	    break;
	  default:
	    gate_count = 1;
            lval_count = 1;
	    break;
      }
}
