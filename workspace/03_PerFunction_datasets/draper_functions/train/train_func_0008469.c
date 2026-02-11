fs_control(Vfs_handle *handle, Vfs_control_op op, va_list ap)
{
  char **pptr;
  Vfs_lock_type lt;

  switch (op) {
  case VFS_GET_CONTAINER:
	pptr = va_arg(ap, char **);
	*pptr = ds_xprintf("file:%s", handle->sd->naming_context);
	break;

  case VFS_SET_LOCK:
	lt = va_arg(ap, int);
	if (lt == VFS_SHLOCK)
	  ;
	else if (lt == VFS_EXLOCK)
	  ;
	else if (lt == VFS_NOLOCK)
	  ;
	else {
	  log_msg((LOG_ERROR_LEVEL, "Invalid control request for lock: %d", lt));
	  return(-1);
	}

    log_msg((LOG_ERROR_LEVEL, "Invalid control request: %d", op));

	break;

  default:
    log_msg((LOG_ERROR_LEVEL, "Invalid control request: %d", op));
    return(-1);

  }

  return(0);
}
