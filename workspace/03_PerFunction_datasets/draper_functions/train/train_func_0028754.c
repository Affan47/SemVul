ConnectSocket(wxIPV4address& address)
{
	return CECSocket::ConnectSocket(StringIPtoUint32(address.IPAddress()),address.Service());
}
