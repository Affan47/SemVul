load()
{
	if ( m_DataIt == m_DataItEnd )
		return;

	while ( m_DataIt != m_DataItEnd )
	{
		switch (*m_DataIt)
		{
		case 'K':
			{
				++m_DataIt;
				if (*m_DataIt == 'a')
				{
					++m_DataIt;
					getColorRGBA( &m_pModel->m_pCurrentMaterial->ambient );
				}
				else if (*m_DataIt == 'd')
				{
					++m_DataIt;
					getColorRGBA( &m_pModel->m_pCurrentMaterial->diffuse );
				}
				else if (*m_DataIt == 's')
				{
					++m_DataIt;
					getColorRGBA( &m_pModel->m_pCurrentMaterial->specular );
				}
				else if (*m_DataIt == 'e')
				{
					++m_DataIt;
					getColorRGBA( &m_pModel->m_pCurrentMaterial->emissive );
				}
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;

		case 'd':
			{
				++m_DataIt;
				getFloatValue( m_pModel->m_pCurrentMaterial->alpha );
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;

		case 'N':
			{
				++m_DataIt;
				switch(*m_DataIt)
				{
				case 's':
					++m_DataIt;
					getFloatValue(m_pModel->m_pCurrentMaterial->shineness);
					break;
				case 'i':
					++m_DataIt;
					getFloatValue(m_pModel->m_pCurrentMaterial->ior);
					break;
				}
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
				break;
			}
			break;


		case 'm':
		case 'b':
			{
				getTexture();
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;

		case 'n':
			{
				createMaterial();
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;

		case 'i':
			{
				m_DataIt = getNextToken<DataArrayIt>(m_DataIt, m_DataItEnd);
				getIlluminationModel( m_pModel->m_pCurrentMaterial->illumination_model );
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;

		default:
			{
				m_DataIt = skipLine<DataArrayIt>( m_DataIt, m_DataItEnd, m_uiLine );
			}
			break;
		}
	}
}
