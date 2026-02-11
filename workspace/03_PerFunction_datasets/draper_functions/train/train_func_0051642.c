des_mode_ebc(struct des * des)
{
	unsigned char block[8];
	int nb_read, bytes, pad, i;

	do {

		bytes = read(des->ifd, &block, sizeof(block));
		nb_read = bytes;
		while (bytes > 0 && nb_read < (int) sizeof(block)) {
			bytes = read(des->ifd, &block[bytes], sizeof(block) - bytes);
			if (bytes > 0)
				nb_read += bytes;
		}

		if (nb_read > 0) {
			pad = 8 - nb_read;
			for (i = pad; i > 0; --i) {
				block[8 - i] = 0;
			}
			des_cipher_block(des, block);
			write(des->ofd, block, sizeof(block));
		}
	} while (bytes > 0);
}
