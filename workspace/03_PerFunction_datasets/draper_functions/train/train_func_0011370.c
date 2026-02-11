create_config_memory()
{
  m_configMemory = new ConfigMemory(this,9);
  m_configMemory->addConfigWord(0,new Config_E(this, "UserID1", 0x8000, true));
  m_configMemory->addConfigWord(1,new Config_E(this, "UserID2", 0x8001, true));
  m_configMemory->addConfigWord(2,new Config_E(this, "UserID3", 0x8002, true));
  m_configMemory->addConfigWord(3,new Config_E(this, "UserID4", 0x8003, true));
  m_configMemory->addConfigWord(6,new Config_E(this, "DeviceID", 0x8006));
  m_configMemory->addConfigWord(7,new Config_E(this, "ConfigW1", 0x8007));
  m_configMemory->addConfigWord(8,new Config_E(this, "ConfigW2", 0x8008));

}
