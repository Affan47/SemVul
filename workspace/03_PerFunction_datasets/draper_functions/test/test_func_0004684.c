bitzi_failure(const struct sha1 *sha1, filesize_t filesize, bitzi_fj_t error)
{
	if (sha1 != NULL) {
		bitzi_data_t dummy;

		ZERO(&dummy);
		dummy.sha1 = sha1;
		dummy.size = filesize;
		dummy.judgment = error;
		gcu_bitzi_result(&dummy);
	}
}
