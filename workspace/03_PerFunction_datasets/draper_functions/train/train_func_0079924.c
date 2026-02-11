breakarm(ptr)
	register struct permonst *ptr;
{
	return ((bigmonst(ptr) || (ptr->msize > MZ_SMALL && !humanoid(ptr)) ||

		ptr == &mons[PM_MARILITH]
		) && !sliparm(ptr));
}
