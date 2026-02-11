v_not(const verinum&left)
{
      verinum val = left;
      for (unsigned idx = 0 ;  idx < val.len() ;  idx += 1)
	    switch (val[idx]) {
		case verinum::V0:
		  val.set(idx, verinum::V1);
		  break;
		case verinum::V1:
		  val.set(idx, verinum::V0);
		  break;
		default:
		  val.set(idx, verinum::Vx);
		  break;
	    }

      return val;
}
