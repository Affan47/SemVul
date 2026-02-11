evaluate_abs(NetExpr*&arg_)
{
      eval_expr(arg_);
      NetEConst*tmpi = dynamic_cast<NetEConst *>(arg_);
      if (tmpi) {
	    verinum arg = tmpi->value();
	    if (arg.is_negative()) {
		  arg = v_not(arg) + verinum(1);
	    }
	    return new NetEConst(arg);
      }

      NetECReal*tmpr = dynamic_cast<NetECReal *>(arg_);
      if (tmpr) {
	    double arg = tmpr->value().as_double();
	    return new NetECReal(verireal(fabs(arg)));
      }

      return 0;
}
