loadEEPROM() {
      scratchpad[2] = (char)attr_thigh->getVal();
      scratchpad[3] = (char)attr_tlow->getVal();
      if(is_ds18b20)
	scratchpad[4] = (char)((attr_config->getVal() & 0x60) | 0x1f);
      scratchpad[8] = calculateCRC8(scratchpad, 8);
  }
