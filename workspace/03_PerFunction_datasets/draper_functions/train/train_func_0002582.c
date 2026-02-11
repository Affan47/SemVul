parse_args( const char *args )
{
     char *buf = alloca( strlen(args) + 1 );

     strcpy( buf, args );

     while (buf && buf[0]) {
          DFBResult  ret;
          char      *value;
          char      *next;

          if ((next = strchr( buf, ',' )) != NULL)
               *next++ = '\0';

          if (strcmp (buf, "help") == 0) {
               print_config_usage();
               exit(1);
          }

          if (strcmp (buf, "memcpy=help") == 0) {
               direct_print_memcpy_routines();
               exit(1);
          }

          if ((value = strchr( buf, '=' )) != NULL)
               *value++ = '\0';

          ret = dfb_config_set( buf, value );
          switch (ret) {
               case DFB_OK:
                    break;
               case DFB_UNSUPPORTED:
                    D_ERROR( "DirectFB/Config: Unknown option '%s'!\n", buf );
                    break;
               default:
                    return ret;
          }

          buf = next;
     }

     return DFB_OK;
}
