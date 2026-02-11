SetMail (const gchar* mail)
{
	g_free (m_mail);
	m_mail = (mail && *mail)? g_strdup (mail): NULL;
}
