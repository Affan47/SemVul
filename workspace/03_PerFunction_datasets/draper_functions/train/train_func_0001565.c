is_cjk_letter(UT_UCSChar c) const
{
    if (!cjk_locale())
	return 0;
    return (c>0xff);
}
