ProbePair(Usb::Device &dev,
			const Usb::EndpointPair &ep,
			uint32_t &pin,
			std::string &desc,
			uint8_t &zeroSocketSequence,
			bool &needClearHalt)
{


	needClearHalt = false;

	Data data;
	dev.BulkDrain(ep.read);
	if( !Intro(0, ep, dev, data) ) {

		dout(_("Probe: Intro(0) failed, retrying after clearing halt"));
		dev.ClearHalt(ep.read);
		dev.ClearHalt(ep.write);
		needClearHalt = true;

		dev.BulkDrain(ep.read);
		if( !Intro(0, ep, dev, data) ) {

			dout(_("Probe: Intro(0) still failed after clearing halt"));
			return false;
		}
	}

	SocketZero socket(dev, ep.write, ep.read);

	Data send, receive;
	ZeroPacket packet(send, receive);


	packet.GetAttribute(SB_OBJECT_INITIAL_UNKNOWN,
		SB_ATTR_INITIAL_UNKNOWN);
	socket.Send(packet);


	packet.GetAttribute(SB_OBJECT_PROFILE, SB_ATTR_PROFILE_PIN);
	socket.Send(packet);
	if( packet.ObjectID() != SB_OBJECT_PROFILE ||
	    packet.AttributeID() != SB_ATTR_PROFILE_PIN ||
	    !ParsePIN(receive, pin) )
	{
		dout(_("Probe: unable to fetch PIN"));
		return false;
	}


	packet.GetAttribute(SB_OBJECT_PROFILE, SB_ATTR_PROFILE_DESC);
	socket.Send(packet);

	if(
	    packet.AttributeID() != SB_ATTR_PROFILE_DESC ||
	    !ParseDesc(receive, desc) )
	{
		dout(_("Probe: unable to fetch description"));
	}


	for( uint16_t attr = 5; attr < 9; attr++ ) {
		packet.GetAttribute(SB_OBJECT_SOCKET_UNKNOWN, attr);
		socket.Send(packet);


	}


	zeroSocketSequence = socket.GetZeroSocketSequence();
	return true;
}
