ClampSpline(int idx, int size)
{
	return ( idx<0 ? size+idx : ( idx>=size ? idx-size : idx ) );
}
