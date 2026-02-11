_GD_ScanFormat(char* fmt, gd_type_t data_type)
{
  dtrace("%p, %x", fmt, data_type);

  switch(data_type) {
    case GD_UINT8:
#ifndef NO_8BIT_INT_PREFIX
      strcpy(fmt, "%" SCNu8);
      break;
#endif
    case GD_UINT16:
      strcpy(fmt, "%" SCNu16);
      break;
    case GD_INT8:
#ifndef NO_8BIT_INT_PREFIX
      strcpy(fmt, "%" SCNi8);
      break;
#endif
    case GD_INT16:
      strcpy(fmt, "%" SCNi16);
      break;
    case GD_UINT32:
      strcpy(fmt, "%" SCNu32);
      break;
    case GD_INT32:
      strcpy(fmt, "%" SCNi32);
      break;
    case GD_UINT64:
      strcpy(fmt, "%" SCNu64);
      break;
    case GD_INT64:
      strcpy(fmt, "%" SCNi64);
      break;
    case GD_FLOAT32:
      strcpy(fmt, "%f");
      break;
    case GD_FLOAT64:
      strcpy(fmt, "%lf");
      break;
    case GD_COMPLEX64:
      strcpy(fmt, "%f;%f");
      break;
    case GD_COMPLEX128:
      strcpy(fmt, "%lf;%lf");
      break;
    default:
      fmt[0] = 0;
      break;
  }

  dreturn("[\"%s\"]", fmt);
}
