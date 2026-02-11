readFromStreamTexturedObject(mrpt::utils::CStream &in)
{
	uint8_t version;
	in >> version;

	CRenderizableDisplayList::notifyChange();

	switch(version)
	{
	case 0:
		{
			in >> m_enableTransparency;
			in >> m_textureImage;
			if (m_enableTransparency)
			{
				in >> m_textureImageAlpha;
				assignImage( m_textureImage, m_textureImageAlpha );
			}
			else
			{
				assignImage( m_textureImage );
			}
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};
	CRenderizableDisplayList::notifyChange();
}
