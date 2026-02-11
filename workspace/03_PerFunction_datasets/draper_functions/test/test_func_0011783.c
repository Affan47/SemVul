isSigPow(Tree sig, Tree& x, int& n)
{

	xtended* p = (xtended*) getUserData(sig);
	if (p == gPowPrim) {
       if (isSigInt(sig->branch(1), &n)) {
			x = sig->branch(0);

			return true;
		}
	}
	return false;
}
