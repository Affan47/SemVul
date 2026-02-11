match_fastboot_with_serial(usb_ifc_info *info, const char *local_serial)
{
    if(!(vendor_id && (info->dev_vendor == vendor_id)) &&
       (info->dev_vendor != 0x18d1) &&
       (info->dev_vendor != 0x8087) &&
       (info->dev_vendor != 0x0451) &&
       (info->dev_vendor != 0x0502) &&
       (info->dev_vendor != 0x0fce) &&
       (info->dev_vendor != 0x05c6) &&
       (info->dev_vendor != 0x22b8) &&
       (info->dev_vendor != 0x0955) &&
       (info->dev_vendor != 0x413c) &&
       (info->dev_vendor != 0x2314) &&
       (info->dev_vendor != 0x0b05) &&
       (info->dev_vendor != 0x0bb4))
            return -1;
    if(info->ifc_class != 0xff) return -1;
    if(info->ifc_subclass != 0x42) return -1;
    if(info->ifc_protocol != 0x03) return -1;


    if (local_serial && (strcmp(local_serial, info->serial_number) != 0 &&
                   strcmp(local_serial, info->device_path) != 0)) return -1;
    return 0;
}
