make_random_key(unsigned char *keybuf)
{
    int i;

#ifdef HAVE_RAND_BYTES
    RAND_bytes(keybuf, 1024);
#elif HAVE_DEV_RANDOM
    read_dev_random(keybuf, 1024);
#else


    for (i = 0; i < 1024; i++)
	keybuf[i] = random() & 0xFF;
#endif

    if (crypto_v0_bugfix)
    {


	for (i = 0; i < 1024; i++)
	    while (keybuf[i] == 0)
		keybuf[i] = random() & 0xFF;
    }
}
