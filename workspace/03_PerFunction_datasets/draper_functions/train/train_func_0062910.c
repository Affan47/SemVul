dump(ostream&o, unsigned ind) const
{
      o << setw(ind) << "";
      dump_lval(o);

      o << " = ";

      if (const NetExpr*de = get_delay())
	    o << "#(" << *de << ") ";

      o << *rval() << ";" << endl;
}
