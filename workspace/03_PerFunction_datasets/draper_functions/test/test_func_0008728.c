setSelected(const wchar_t *item)
{
	s32 index = -1;

	if ( item )
	{
		for ( index = 0; index < (s32) Items.size(); ++index )
		{
			if ( Items[index].text == item )
				break;
		}
	}
	setSelected ( index );
}
