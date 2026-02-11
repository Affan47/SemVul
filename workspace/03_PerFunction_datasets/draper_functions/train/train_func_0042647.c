textMessage( uint id, ushort sequence, const ByteArray& key,

		int toId, const ByteArray& transferKey, ByteArray& message )
	{
		ByteArray text( 65536 );
		text += messageHeader( id, toId, transferKey, IMText, sequence, time(NULL));
		text += encodeMessage( message );
		return Packet::create(id, Command::SendMsg, sequence, key, text );
	}
