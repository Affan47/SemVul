mono_tls_key_get_offset (MonoTlsKey key)
{
	g_assert (tls_offset_set [key]);
	return tls_offsets [key];
}
