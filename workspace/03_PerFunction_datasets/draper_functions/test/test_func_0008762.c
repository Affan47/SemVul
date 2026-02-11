cleanUp() {
	if (m_Data != NULL) {
		if (((encodeState*)m_Data)->enc_hashtab != NULL) {
			free(((encodeState*)m_Data)->enc_hashtab);
		}
		free(m_Data);
		m_Data = NULL;
	}
}
