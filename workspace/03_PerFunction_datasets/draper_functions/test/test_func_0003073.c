elaborate_pexpr(Design*des, NetScope*sc) const
{
      cerr << get_fileline() << ": error: invalid parameter expression: "
	   << *this << endl;
      des->errors += 1;

      return 0;
}
