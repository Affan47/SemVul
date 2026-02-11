paint()
{
	for( int i = 0; i < geta_num; ++i )
	{
		geta_array[i].paint(focused_geta == i);
	}
}
