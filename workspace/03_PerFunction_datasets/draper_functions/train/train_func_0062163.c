create_config_memory()
{
  m_configMemory = new ConfigMemory(this,1);
  m_configMemory->addConfigWord(0,new ConfigWord("CONFIG", 0xfff,"Configuration Word",this,0xfff));


}
