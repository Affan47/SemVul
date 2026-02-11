endSection()
{
	Assert( cfp );
	Assert( m_size_offset > 0 );

	size_t cur = cftell(cfp);

	Assert( cur >= m_size_offset );

	size_t section_size = cur - m_size_offset;

	if (section_size) {

		cfseek(cfp, cur - section_size - sizeof(int), CF_SEEK_SET);
		cfwrite_int((int)section_size, cfp);


		cfseek(cfp, cur, CF_SEEK_SET);
	}
}
