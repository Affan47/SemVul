name(char *buff,int len)
  {
    if (!buff)
      return buff;

    char cpBase[256];
    char cpSource[256];
    char cpDestination[256];

    switch(m_addrMode) {
    case eRegisterDirect:
      snprintf(buff, len, "%s%s\t%s, %s",
	       instruction::name().c_str(),
	       (m_bByteOperation ? ".b" :""),
	       m_source->name(cpBase,sizeof(cpBase)),
	       m_destination->name(cpDestination,sizeof(cpDestination))
	       );
      break;
    case eRegisterIndirect:
      snprintf(buff, len, "%s%s\t%s,%s,%s",
	       instruction::name().c_str(),
	       (m_bByteOperation ? ".b" :""),
	       m_base->name(cpBase,sizeof(cpBase)),
	       m_source->name(cpSource,sizeof(cpSource)),
	       m_destination->name(cpDestination,sizeof(cpDestination))
	       );
      break;
    default:
      break;
    }

    return buff;
  }
