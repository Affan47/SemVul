addr_to_str(u8* data, u8 ip_ver) {

  static char tmp[128];


  if (ip_ver == IP_VER4) {

    sprintf(tmp, "%u.%u.%u.%u", data[0], data[1], data[2], data[3]);

  } else {

    sprintf(tmp, "%x:%x:%x:%x:%x:%x:%x:%x",
            (data[0] << 8) | data[1], (data[2] << 8) | data[3],
            (data[4] << 8) | data[5], (data[6] << 8) | data[7],
            (data[8] << 8) | data[9], (data[10] << 8) | data[11],
            (data[12] << 8) | data[13], (data[14] << 8) | data[15]);

  }

  return (u8*)tmp;

}
