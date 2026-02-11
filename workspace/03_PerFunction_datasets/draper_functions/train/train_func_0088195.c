delay_type_from_expr(const NetExpr*expr)
{
      DelayType result = POSSIBLE_DELAY;

      if (const NetEConst*e = dynamic_cast<const NetEConst*>(expr)) {
	    if (e->value().is_zero()) result = ZERO_DELAY;
	    else result = DEFINITE_DELAY;
      }

      if (const NetECReal*e = dynamic_cast<const NetECReal*>(expr)) {
	    if (e->value().as_double() == 0.0) result = ZERO_DELAY;
	    else result = DEFINITE_DELAY;
      }

      return result;
}
