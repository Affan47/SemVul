mkrep( mach, lb, ub )
int mach, lb, ub;
	{
	int base_mach, tail, copy, i;

	base_mach = copysingl( mach, lb - 1 );

	if ( ub == INFINITY )
		{
		copy = dupmachine( mach );
		mach = link_machines( mach,
		link_machines( base_mach, mkclos( copy ) ) );
		}

	else
		{
		tail = mkstate( SYM_EPSILON );

		for ( i = lb; i < ub; ++i )
			{
			copy = dupmachine( mach );
			tail = mkopt( link_machines( copy, tail ) );
			}

		mach = link_machines( mach, link_machines( base_mach, tail ) );
		}

	return mach;
	}
