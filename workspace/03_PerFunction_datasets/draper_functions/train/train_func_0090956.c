GetType() const
	{
		if(!m_pContent)
			return CT_NONE;

		if(m_pContent->IsScalar())
			return CT_SCALAR;
		else if(m_pContent->IsSequence())
			return CT_SEQUENCE;
		else if(m_pContent->IsMap())
			return CT_MAP;

		return CT_NONE;
	}
