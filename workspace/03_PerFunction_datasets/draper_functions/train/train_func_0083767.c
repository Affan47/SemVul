eval_eqeq_real_(NetExpr*le, NetExpr*ri, bool ne_flag)
{
      NetEConst*vtmp;
      NetECReal*rtmp;
      double lv, rv;

      switch (le->expr_type()) {
	  case IVL_VT_REAL:
	    rtmp = dynamic_cast<NetECReal*> (le);
	    if (rtmp == 0) return 0;
	    lv = rtmp->value().as_double();
	    break;

	  case IVL_VT_LOGIC:
	  case IVL_VT_BOOL:
	    vtmp = dynamic_cast<NetEConst*> (le);
	    if (vtmp == 0) return 0;
	    lv = vtmp->value().as_double();
	    break;

	  default:
	    lv = 0.0;
	    cerr << get_fileline() << ": internal error: "
		 << "Unexpected expression type? " << le->expr_type() << endl;
	    assert(0);
      }

      switch (ri->expr_type()) {
	  case IVL_VT_REAL:
	    rtmp = dynamic_cast<NetECReal*> (ri);
	    if (rtmp == 0) return 0;
	    rv = rtmp->value().as_double();
	    break;

	  case IVL_VT_LOGIC:
	  case IVL_VT_BOOL:
	    vtmp = dynamic_cast<NetEConst*> (ri);
	    if (vtmp == 0) return 0;
	    rv = vtmp->value().as_double();
	    break;

	  default:
	    rv = 0.0;
	    cerr << get_fileline() << ": internal error: "
		 << "Unexpected expression type? " << ri->expr_type() << endl;
	    assert(0);
      }

      verinum result(((lv == rv) ^ ne_flag) ? verinum::V1 : verinum::V0, 1);
      vtmp = new NetEConst(result);
      vtmp->set_line(*this);

      return vtmp;
}
