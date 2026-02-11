init ( unsigned int n )
{

	bvec bZero ( n, false );
	nvec nZero ( n, 0 );


	M.insert ( M.end(), n, bZero );
	MStar.insert ( MStar.end(), n, bZero );
	MMinus.insert ( MMinus.end(), n, bZero );
#ifndef FPP_NO_DELETE_EDGE
	N.insert ( N.end(), n, nZero );
#endif
	M_c.insert ( M_c.end(), n, nZero );


	V_c.insert ( V_c.end(), n, true );
#ifndef FPP_NO_DELETE_EDGE
	e_c.insert ( e_c.end(), n, 0 );
#endif

	C_c.resize(n);
	for ( Vertex i = 0; i < n; ++i )
	{
		L.push_back(i);
		C_c[i].push_back(i);
	}


#ifndef FPP_NO_DELETE_EDGE
	S.resize(n);
	P.resize(n);
#endif
	S_c.resize(n);
	P_c.resize(n);

	last = n;
}
