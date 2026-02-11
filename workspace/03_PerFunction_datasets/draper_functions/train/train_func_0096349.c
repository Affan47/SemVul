gw_string_buffer_resize ( GWStringBuffer *p, gulong newsize)
{
	gchar *ptr = NULL;
	gulong result = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p  != NULL )
	{

		if ( newsize >= p->size )
		{
			if ( p->buff != NULL )
			{


				ptr = (gchar*)g_realloc ( p->buff, sizeof ( gchar)*(newsize+1));

				if ( ptr != NULL )
				{
					p->buff = ptr;
					memset(&p->buff[p->size+1],'\0',newsize-p->size);
					result = newsize + 1;
				}
				else
				{
					result = 0;
				}
			}
			else
			{
				if ( (p->buff = (gchar*)g_malloc0 ( sizeof ( gchar)*(newsize+1))) != NULL )
				{
					result = newsize + 1;
				}
				else
				{
					result = 0;
				}
			}

			p->size = result;
		}
	}

	return result;
}
