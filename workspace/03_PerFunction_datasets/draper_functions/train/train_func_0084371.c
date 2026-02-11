SendOOBFromRakNetPort(OutOfBandIdentifiers oob, BitStream *extraData, SystemAddress sa)
{
	RakNet::BitStream oobBs;
	oobBs.Write((unsigned char)oob);
	if (extraData)
	{
		extraData->ResetReadPointer();
		oobBs.Write(*extraData);
	}
	char ipAddressString[32];
	sa.ToString(false, ipAddressString);
	rakPeerInterface->SendOutOfBand((const char*) ipAddressString,sa.GetPort(),(const char*) oobBs.GetData(),oobBs.GetNumberOfBytesUsed());
}
