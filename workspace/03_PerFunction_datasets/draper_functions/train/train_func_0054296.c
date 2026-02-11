license_write_new_license_request_packet(rdpLicense* license, STREAM* s)
{
	stream_write_uint32(s, KEY_EXCHANGE_ALG_RSA);
	license_write_platform_id(license, s);
	stream_write(s, license->client_random, 32);
	license_write_padded_binary_blob(s, license->encrypted_premaster_secret);
	license_write_binary_blob(s, license->client_user_name);
	license_write_binary_blob(s, license->client_machine_name);
}
