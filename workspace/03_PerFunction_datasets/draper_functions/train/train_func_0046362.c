info(unsigned inf) const
{
	if (inf == info_flags::list)
		return true;
	else
		return inherited::info(inf);
}
