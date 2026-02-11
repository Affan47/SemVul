real_fail_neg( int eval, const char *eval_str, const char *func, const char *file, int line )
{
	if ( eval < 0 )
	{
		string exc;
		ostringstream sb;

		sb << file << ":" << line << ": In function \"" << func << "\": \"" << eval_str << "\" evaluated to " << eval;
		if ( errno != 0 )
			sb << endl << file << ":" << line << ": errno: " << errno << " (" << strerror( errno ) << ")";
		sb << ends;
		exc = sb.str();
		cerr << exc << endl;
		throw exc;
	}
}
