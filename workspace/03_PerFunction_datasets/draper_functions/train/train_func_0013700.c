recursive(int recursion)
{


	MY_PROFILE(CProfileScope p3(L"recursive", L"grp runtime");)
	if (recursion > 0 )
		recursive(recursion-1);
}
