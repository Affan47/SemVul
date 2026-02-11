i18n_key_analyze(XKeyEvent * , KeySym * key,
			    char *keyName, int nbytes)
{
    KeySym t = (unsigned char) keyName[0];


    if ((nbytes == 1) && *key < KEYBYTEMAX)
	*key = t;
#ifdef USE_HACK_FOR_BAD_XSERVER


    else if (!nbytes && (*key > KEYMASK) && (*key < KEYBYTEMAX)) {
	*key &= KEYMASK;
	keyName[0] = *key & KEYMASK;
	nbytes = 1;
    }
#endif
    return nbytes;
}
