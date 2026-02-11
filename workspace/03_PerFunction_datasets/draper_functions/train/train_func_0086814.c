get_parameter(const char* key,
				       const NetExpr*&msb,
				       const NetExpr*&lsb) const
{
      map<perm_string,param_expr_t>::const_iterator idx;

      idx = parameters.find(perm_string::literal(key));
      if (idx != parameters.end()) {
	    msb = (*idx).second.msb;
	    lsb = (*idx).second.lsb;
	    return (*idx).second.expr;
      }

      idx = localparams.find(perm_string::literal(key));
      if (idx != localparams.end()) {
	    msb = (*idx).second.msb;
	    lsb = (*idx).second.lsb;
	    return (*idx).second.expr;
      }

      return 0;
}
