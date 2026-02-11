AddUploaded(uint32 bytes, uint32 dwForIP, bool cryptoavail)
{
	switch (GetCurrentIdentState(dwForIP)) {
		case IS_IDFAILED:
		case IS_IDBADGUY:
		case IS_IDNEEDED:
			if (cryptoavail) {
				return;
			}
			break;
	 	case IS_NOTAVAILABLE:
	 	case IS_IDENTIFIED:
			break;
	}

	m_pCredits->uploaded += bytes;
}
