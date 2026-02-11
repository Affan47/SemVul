decrypt_packet() {

	unsigned char blocksize;
	unsigned char macsize;
	unsigned int padlen;
	unsigned int len;

	TRACE(("enter decrypt_packet"))
	blocksize = ses.keys->recv_algo_crypt->blocksize;
	macsize = ses.keys->recv_algo_mac->hashsize;

	ses.kexstate.datarecv += ses.readbuf->len;


	buf_setpos(ses.readbuf, blocksize);

	buf_resize(ses.decryptreadbuf, ses.readbuf->len - macsize);
	buf_setlen(ses.decryptreadbuf, ses.decryptreadbuf->size);
	buf_setpos(ses.decryptreadbuf, blocksize);


	while (ses.readbuf->pos < ses.readbuf->len - macsize) {
		if (ses.keys->recv_crypt_mode->decrypt(
					buf_getptr(ses.readbuf, blocksize),
					buf_getwriteptr(ses.decryptreadbuf, blocksize),
					blocksize,
					&ses.keys->recv_cipher_state) != CRYPT_OK) {
			dropbear_exit("error decrypting");
		}
		buf_incrpos(ses.readbuf, blocksize);
		buf_incrwritepos(ses.decryptreadbuf, blocksize);
	}


	buf_setpos(ses.readbuf, ses.readbuf->len - macsize);
	if (checkmac(ses.readbuf, ses.decryptreadbuf) != DROPBEAR_SUCCESS) {
		dropbear_exit("Integrity error");
	}


	buf_free(ses.readbuf);
	ses.readbuf = NULL;


	buf_setpos(ses.decryptreadbuf, PACKET_PADDING_OFF);
	padlen = buf_getbyte(ses.decryptreadbuf);


	len = ses.decryptreadbuf->len - padlen - 4 - 1;
	if ((len > RECV_MAX_PAYLOAD_LEN) || (len < 1)) {
		dropbear_exit("bad packet size");
	}

	buf_setpos(ses.decryptreadbuf, PACKET_PAYLOAD_OFF);

#ifndef DISABLE_ZLIB
	if (is_compress_recv()) {

		ses.payload = buf_decompress(ses.decryptreadbuf, len);
	} else
#endif
	{

		ses.payload = buf_new(len);
		memcpy(ses.payload->data, buf_getptr(ses.decryptreadbuf, len), len);
		buf_incrlen(ses.payload, len);
	}

	buf_free(ses.decryptreadbuf);
	ses.decryptreadbuf = NULL;
	buf_setpos(ses.payload, 0);

	ses.recvseq++;

	TRACE(("leave decrypt_packet"))
}
