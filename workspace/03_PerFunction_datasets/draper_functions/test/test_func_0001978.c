errno_to_stscode()
{
    switch (errno)
    {
    case 0:         return 0225;
    case EPERM:     return 0125;
    case ENOENT:    return 062;
    case EINTR:     return 011;
    case EIO:       return 02;
    case ENXIO:     return 035;
    case ENOMEM:    return 037;
    case EACCES:    return 0125;
    case EBUSY:     return 041;
    case EEXIST:    return 055;
    case ENODEV:    return 035;
    case ENOTDIR:   return 040;
    case EINVAL:    return 0203;
    case ENFILE:
    case EMFILE:    return 0307;
    case ETXTBSY:   return 060;
    case EFBIG:     return 0301;
    case EROFS:     return 0164;
    case ENOTCONN:  return 01;
    case ENOSPC:    return 065;
    default:
	DAPLOG((LOG_DEBUG, "no DAP error for %d - sending default\n", errno));
	return 01;
    }
}
