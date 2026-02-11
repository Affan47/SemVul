Register(const char **const notifications, const int notifications_count)
{
	if( protocol == GROWL_TCP )
	{
		growl_tcp_register( server , application , notifications , notifications_count , password );
	}
	else
	{
		growl_udp_register( server , application , notifications , notifications_count , password );
	}
}
