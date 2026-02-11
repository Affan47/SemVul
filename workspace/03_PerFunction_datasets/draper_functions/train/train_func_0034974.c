IsAcceptableContact(const CContact *toCheck) const
{


	if (toCheck->GetVersion() <= 1) {

		return false;
	}
	CContact *duplicate = GetContact(toCheck->GetClientID());
	if (duplicate != NULL) {
		if ((duplicate->IsIPVerified() && duplicate->GetIPAddress() != toCheck->GetIPAddress()) || duplicate->GetUDPPort() != toCheck->GetUDPPort()) {

			return false;
		} else {

			return true;
		}
	}

	return CRoutingBin::CheckGlobalIPLimits(toCheck->GetIPAddress(), toCheck->GetUDPPort());
}
