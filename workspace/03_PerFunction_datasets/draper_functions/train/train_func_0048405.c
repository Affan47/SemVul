setAllVertices( const std::vector<double> &x, const std::vector<double> &y )
{
	ASSERT_(x.size()==y.size() && !x.empty());
	setAllVertices( x.size() ,&x[0],&y[0] );
}
