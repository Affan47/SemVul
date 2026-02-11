mflash_mark_as_used(int index)
{
	if (index < 0)
		return;

	Assert( index < (int)Mflash_info.size() );

	Mflash_info[index].used_this_level++;
}
