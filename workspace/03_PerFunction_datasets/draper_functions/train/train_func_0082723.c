render(GemState *state)
{
  gem::image::load::poll();


  if (!m_loadedImage){
    return;
  }


  if (m_cache&&m_cache->resendImage)
    {
      m_loadedImage->refreshImage(&m_pixBlock.image);
      m_pixBlock.newimage = 1;
      m_cache->resendImage = 0;
    }
  state->set(GemState::_PIX, &m_pixBlock);
}
