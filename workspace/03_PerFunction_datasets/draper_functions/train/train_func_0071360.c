setTexture(const Texture::Texture *texture)
{
	m_texture = texture;
	if (m_texture)
	{
		m_lSource = TEXTURE;
	}
	else
	{
		m_lSource = CONSTANT;
	}
}
