openDeviceBySerial(const unsigned int SerialRequired){
  std::set<unsigned> serial_required;
  serial_required.insert(SerialRequired);
  return openDevicesBySerialNum(serial_required);
}
