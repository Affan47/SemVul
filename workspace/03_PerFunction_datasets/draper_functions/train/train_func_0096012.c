_e2pcr_crypt_buffer (guint8 hashes[KEY_LENGTH],
	guint8 *iseed, guint8 *jseed, gpointer filebuffer, csize_t filebuffersize)
{
	guchar *encryptedbufferp, *filebufferp;
	csize_t indx;
	guint8 i, j, temp;

	encryptedbufferp = filebufferp = filebuffer;
	i = *iseed;
	j = *jseed;

	for (indx = 0; indx < filebuffersize; indx++)
	{
		j += hashes[i];
		*encryptedbufferp++ = *filebufferp ^ hashes[(guint8)(hashes[i] + hashes[j])];
		SWAP(hashes[i], hashes[j]);
		i++;
		filebufferp++;
	}
	*iseed = i;
	*jseed = j;
}
