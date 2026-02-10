writeIncomingMessage(const QByteArray &packet, bool *notStun, const QHostAddress &from_addr, int from_port)
	{
		if(!checkActiveAndFrom(from_addr, from_port))
		{

			*notStun = false;
			return false;
		}

		int validationFlags = 0;
		StunMessage msg = parse_stun_message(packet, &validationFlags, key);
		if(msg.isNull())
		{

			*notStun = true;
			return false;
		}

		if(fpRequired && !(validationFlags & StunMessage::Fingerprint))
		{


			*notStun = true;
			return false;
		}

		processIncoming(msg, (validationFlags & StunMessage::MessageIntegrity) ? true : false);
		return true;
	}
