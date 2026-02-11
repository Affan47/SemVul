toString() const
{
  std::ostringstream os;
  os << dashes << std::endl
     << _("Message type: SMS-DELIVER-REPORT") << std::endl
     << _("SC address: '") << _serviceCentreAddress._number << "'" << std::endl
     << _("Protocol identifier present: ") << _protocolIdentifierPresent
     << std::endl
     << _("Data coding scheme present: ") << _dataCodingSchemePresent << std::endl
     << _("User data length present: ") << _userDataLengthPresent << std::endl;
  if (_protocolIdentifierPresent)
    os << _("Protocol identifier: 0x") << std::hex
       << (unsigned int)_protocolIdentifier
       << std::dec << std::endl;
  if (_dataCodingSchemePresent)
    os << _("Data coding scheme: ") << _dataCodingScheme.toString() << std::endl;
  if (_userDataLengthPresent)
    os << _("User data length: ") << (int)userDataLength() << std::endl
       << _("User data: '") << _userData << "'" << std::endl;
  os << dashes << std::endl << std::endl
     << std::ends;
  return os.str();
}
