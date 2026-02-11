read_datalog_info(unsigned int* seg1_addr, unsigned int* seg1_len,
                  unsigned int* seg2_addr, unsigned int* seg2_len)
{
  unsigned char  info[16];
  unsigned int   flash_start_addr;
  unsigned int   flash_length;
  unsigned int   data_start_addr;
  unsigned int   next_blank_addr;

  write_packet(PID_INFO_DATALOG, NULL, 0);
  read_packet(PID_DATA, info, sizeof(info), sizeof(info), FALSE);

  flash_start_addr = le_read32(info);
  flash_length = le_read32(info + 4);
  data_start_addr = le_read32(info + 8);
  next_blank_addr = le_read32(info + 12);

  if (data_start_addr > next_blank_addr) {

    *seg1_addr = data_start_addr;
    *seg1_len = flash_start_addr + flash_length - *seg1_addr;
    *seg2_addr = flash_start_addr;
    *seg2_len = next_blank_addr - flash_start_addr;
  } else {

    *seg1_addr = data_start_addr;
    *seg1_len = next_blank_addr - data_start_addr;
    *seg2_addr = 0;
    *seg2_len = 0;
  }

  if (*seg1_len & 0x1F || *seg2_len & 0x1F) {
    fatal(MYNAME ": Protocol error: datalog lengths %u, %u "
          "not aligned to 32 bytes\n", *seg1_len, *seg2_len);
  }
}
