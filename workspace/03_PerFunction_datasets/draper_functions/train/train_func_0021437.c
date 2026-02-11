operator()(Pkg* left, Pkg* right) const
{
	return (this->*mSortFunc)(right, left);
}
