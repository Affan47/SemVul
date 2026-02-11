eval_tree(int prune_to_width)
{
      eval_expr(expr_);
      if (expr_type() == IVL_VT_REAL) return eval_tree_real_();

      NetEConst*rval = dynamic_cast<NetEConst*>(expr_);
      if (rval == 0) return 0;

      verinum val = rval->value();
      verinum::V res;
      bool invert = false;

      switch (op_) {

	  case '!': {


		unsigned v1 = 0, vx = 0;
		for (unsigned idx = 0 ;  idx < val.len() ;  idx += 1) {
		      switch (val.get(idx)) {
			  case verinum::V0:
			    break;
			  case verinum::V1:
			    v1 += 1;
			    break;
			  default:
			    vx += 1;
			    break;
		      }
		}

		res = v1? verinum::V0 : (vx? verinum::Vx : verinum::V1);
		break;
	  }

	  case 'A':
		invert = true;
	  case '&': {
		res = verinum::V1;
		for (unsigned idx = 0 ;  idx < val.len() ;  idx += 1)
		      res = res & val.get(idx);
		break;
	  }

	  case 'N':
		invert = true;
	  case '|': {
		res = verinum::V0;
		for (unsigned idx = 0 ;  idx < val.len() ;  idx += 1)
		      res = res | val.get(idx);
		break;
	  }

	  case 'X':
		invert = true;
	  case '^': {

		unsigned ones = 0, unknown = 0;
		for (unsigned idx = 0 ;  idx < val.len() ;  idx += 1)
		      switch (val.get(idx)) {
			  case verinum::V0:
			    break;
			  case verinum::V1:
			    ones += 1;
			    break;
			  default:
			    unknown += 1;
			    break;
		      }

		if (unknown) res = verinum::Vx;
		else if (ones%2) res = verinum::V1;
		else res = verinum::V0;
		break;
	  }

	  default:
	    return 0;
      }

      if (invert) res = ~res;
      return new NetEConst(verinum(res, 1));
}
