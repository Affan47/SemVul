jshSetFlowControlEnabled(IOEventFlags device, bool xOnXOff) {
  if (!DEVICE_IS_USART(device)) return;
  JshSerialDeviceState *deviceState = &jshSerialDeviceStates[device-EV_USBSERIAL];
  if (xOnXOff)
    (*deviceState) |= SDS_FLOW_CONTROL_XON_XOFF;
  else
    (*deviceState) &= ~SDS_FLOW_CONTROL_XON_XOFF;
}
