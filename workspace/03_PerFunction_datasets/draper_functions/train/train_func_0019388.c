pci_config_in32( unsigned int bus,
                            unsigned int slot,
                            unsigned int func,
                            u8 reg )
{
     char  filename[512];
     int   fd;
     u32 val;

     snprintf( filename, 512,
               "/proc/bus/pci/%02x/%02x.%x",
               bus, slot, func );

     fd = open( filename, O_RDONLY );
     if (fd < 0)
          return 0;

     if (lseek( fd, reg, SEEK_SET ) != reg) {
          close( fd );
          return 0;
     }

     if (read( fd, &val, 4 ) != 4) {
          close( fd );
          return 0;
     }

     close( fd );

#ifdef WORDS_BIGENDIAN
     return ((val & 0xff000000) >> 24) |
            ((val & 0x00ff0000) >>  8) |
            ((val & 0x0000ff00) <<  8) |
            ((val & 0x000000ff) << 24);
#else
     return val;
#endif
}
