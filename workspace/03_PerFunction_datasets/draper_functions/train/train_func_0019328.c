getFileNoExtString( string oFileName )
{
	string::size_type i = oFileName.rfind('/');
	if( i != string::npos )
		oFileName.erase(0, i + 1);
	i = oFileName.rfind('.');
	if( i != string::npos )
		oFileName.erase( i, string::npos);
	return oFileName;
}
