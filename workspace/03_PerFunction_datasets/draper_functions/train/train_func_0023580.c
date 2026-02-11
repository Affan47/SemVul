cleanImage()
{

  if (m_loadedImage)
    {
      delete m_loadedImage;
      m_loadedImage = NULL;
      m_pixBlock.image.clear();
      m_pixBlock.image.data = NULL;
    }
}
