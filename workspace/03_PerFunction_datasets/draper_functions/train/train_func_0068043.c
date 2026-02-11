url() const
{
	GooString * goo = m_movieData->m_movieObj->getFileName();
	return goo ? QString( goo->getCString() ) : QString();
}
