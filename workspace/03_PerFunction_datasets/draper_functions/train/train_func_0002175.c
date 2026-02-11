mini_get_tls_offset (MonoTlsKey key)
{
	int offset;
	g_assert (MONO_ARCH_HAVE_TLS_GET);

	switch (key) {
	case TLS_KEY_THREAD:
		offset = mono_thread_get_tls_offset ();
		break;
	case TLS_KEY_JIT_TLS:
		offset = mono_get_jit_tls_offset ();
		break;
	case TLS_KEY_DOMAIN:
		offset = mono_domain_get_tls_offset ();
		break;
	case TLS_KEY_LMF:
		offset = mono_get_lmf_tls_offset ();
		break;
	case TLS_KEY_LMF_ADDR:
		offset = mono_get_lmf_addr_tls_offset ();
		break;
	default:
		offset = mono_tls_key_get_offset (key);
		g_assert (offset != -1);
		break;
	}

	return offset;
}
