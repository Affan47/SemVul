checkHorizontal()
{
	if(m_horizontal>1.0f){
		m_horizontal = 1.0f;
	}else if(m_horizontal<0.0f){
		m_horizontal = 0.0f;
	}
}
