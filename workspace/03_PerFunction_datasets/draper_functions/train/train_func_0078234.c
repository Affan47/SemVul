net_init(NET_NODE* _node, const int _port)
{
#ifdef _DEBUG
	L_DEBUG( "(0x%08x, %d)\n",
		_node, _port
		);
#endif

	if ( !_node )
	{
		L_ERROR( "_node = NULL\n","" );

		return false;
	}

	if ( _port < 1024 || _port > 65535 )
	{
		L_ERROR( "incorrect port: %d\n",
			_port
			);

		return false;
	}

	memset( (void*)_node, 0, sizeof(_node) );

	_node->sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	if ( _node->sock < 0 )
	{
		L_ERROR( "create socket error %d: %s\n",
			errno, strerror(errno)
			);

		return false;
	}

	int on = 1;
	if ( setsockopt( _node->sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on) ) < 0 )
	{
		L_ERROR( "setsockopt error %d: %s\n",
			errno, strerror(errno)
			);

		return false;
	}

	_node->sadr.sin_family = AF_INET;
	_node->sadr.sin_addr.s_addr = INADDR_BROADCAST;
	_node->sadr.sin_port = htons(_port);

	L_LOG( "create broadcast socket on port %d\n",
		_port
		);

	return true;
}
