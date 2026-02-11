isLoggedIn()
{
    if (isVersion1Key) {
	if (reverify) {
	    testNonce();
	}
	return nonceValid;
    }
    return loggedIn;
}
