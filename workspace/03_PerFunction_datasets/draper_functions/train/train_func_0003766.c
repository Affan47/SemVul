__nis_finddirectory (directory_obj *dir, const_nis_name name)
{
  nis_error status;
  fd_args fd_args;
  fd_result *fd_res;

  fd_args.dir_name = (char *)name;
  fd_args.requester = nis_local_host();
  fd_res = calloc (1, sizeof (fd_result));
  if (fd_res == NULL)
    return NULL;

  status = __do_niscall2 (dir->do_servers.do_servers_val,
			  dir->do_servers.do_servers_len,
			  NIS_FINDDIRECTORY, (xdrproc_t) _xdr_fd_args,
			  (caddr_t) &fd_args, (xdrproc_t) _xdr_fd_result,
			  (caddr_t) fd_res, NO_AUTHINFO|USE_DGRAM, NULL);
  if (status != NIS_SUCCESS)
    fd_res->status = status;

  return fd_res;
}
