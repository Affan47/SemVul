textureMess(int mode)
{
  if(mode<0){
    error("textureMode must be >= 0");
    return;
  }
  m_textureMode = mode;
  setModified();
  alreadyInit=0;

}
