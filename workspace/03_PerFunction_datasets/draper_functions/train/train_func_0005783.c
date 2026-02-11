USB_ReqGetDescriptor (void) {
  uint8_t  *pD;
  uint32_t len, n;

  switch (SetupPacket.bmRequestType.BM.Recipient) {
    case REQUEST_TO_DEVICE:
      switch (SetupPacket.wValue.WB.H) {
        case USB_DEVICE_DESCRIPTOR_TYPE:
          EP0Data.pData = (uint8_t *)USB_DeviceDescriptor;
          len = USB_DEVICE_DESC_SIZE;
          break;
        case USB_CONFIGURATION_DESCRIPTOR_TYPE:
          pD = (uint8_t *)USB_ConfigDescriptor;
          for (n = 0; n != SetupPacket.wValue.WB.L; n++) {
            if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength != 0) {
              pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
            }
          }
          if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength == 0) {
            return (FALSE);
          }
          EP0Data.pData = pD;
          len = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
          break;
        case USB_STRING_DESCRIPTOR_TYPE:
          pD = (uint8_t *)USB_StringDescriptor;
          for (n = 0; n != SetupPacket.wValue.WB.L; n++) {
            if (((USB_STRING_DESCRIPTOR *)pD)->bLength != 0) {
              pD += ((USB_STRING_DESCRIPTOR *)pD)->bLength;
            }
          }
          if (((USB_STRING_DESCRIPTOR *)pD)->bLength == 0) {
            return (FALSE);
          }
          EP0Data.pData = pD;
          len = ((USB_STRING_DESCRIPTOR *)EP0Data.pData)->bLength;
          break;
        default:
          return (FALSE);
      }
      break;
    case REQUEST_TO_INTERFACE:
      switch (SetupPacket.wValue.WB.H) {
#if USB_HID
        case HID_HID_DESCRIPTOR_TYPE:
          if (SetupPacket.wIndex.WB.L != USB_HID_IF_NUM) {
            return (FALSE);
          }
          EP0Data.pData = (uint8_t *)USB_ConfigDescriptor + HID_DESC_OFFSET;
          len = HID_DESC_SIZE;
          break;
        case HID_REPORT_DESCRIPTOR_TYPE:
          if (SetupPacket.wIndex.WB.L != USB_HID_IF_NUM) {
            return (FALSE);
          }
          EP0Data.pData = (uint8_t *)HID_ReportDescriptor;
          len = HID_ReportDescSize;
          break;
        case HID_PHYSICAL_DESCRIPTOR_TYPE:
          return (FALSE);
#endif
        default:
          return (FALSE);
      }
      break;
    default:
      return (FALSE);
  }

  if (EP0Data.Count > len) {
    EP0Data.Count = len;
  }

  return (TRUE);
}
