unencrypt_new(char *scrambled_text, int scrambled_len, char *text, int *text_len)
{
	ushort lvl1_block[NUM_LVL1_KEYS * 2];
	ushort lvl1_block_copy[NUM_LVL1_KEYS * 2];
	ushort block_checksum;
	int block_size, idx;
	uint encrypt_id;


	memcpy(&encrypt_id, scrambled_text, 4);
	if (encrypt_id != Encrypt_new_signature) {
		memcpy(text, scrambled_text, scrambled_len);
		*text_len = scrambled_len;
		return;
	}


	*text_len = 0;
	scrambled_text += 4;
	scrambled_len -= 4;
	block_checksum = 0xffff;
	while(*text_len < scrambled_len){

		if((scrambled_len - *text_len) < (NUM_LVL1_KEYS * 2)){
			memcpy(lvl1_block, scrambled_text + *text_len, scrambled_len - *text_len);
			block_size = scrambled_len - *text_len;
		}

		else {
			memcpy(lvl1_block, scrambled_text + *text_len, NUM_LVL1_KEYS * 2);
			block_size = NUM_LVL1_KEYS * 2;
		}


		memcpy(lvl1_block_copy, lvl1_block, block_size);

		for(idx=0; idx<block_size/2; idx++){
			lvl1_block[idx] ^= (Lvl1_keys[idx] ^ block_checksum);
		}


		block_checksum = chksum_add_short(block_checksum, (char*)lvl1_block_copy, block_size);


		memcpy(text + *text_len, lvl1_block, block_size);
		*text_len += block_size;
	}
}
