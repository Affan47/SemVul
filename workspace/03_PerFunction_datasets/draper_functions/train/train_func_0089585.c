rootp (const cl_I& x, uintL n, cl_I* w)
{
	if (eq(x,0) || eq(x,1))
	  { *w = x; return true; }
	if (n >= integer_length(x))
	  { return false; }
	return cl_rootp_aux(x,n,w);
}

}
