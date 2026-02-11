autodir_setname(const char *name)
{
	int i = 0;
	int start = 0;

	self.name[ 0 ] = 0;
	for( i = 0 ; name[ i ] ; i++ )
		if( name[ i ] == '/' )
			start = i + 1;

	string_n_copy( self.name, name + start, sizeof(self.name) );
}
