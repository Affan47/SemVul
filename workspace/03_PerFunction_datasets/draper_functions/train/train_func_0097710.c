_assuan_system_hooks_copy (assuan_system_hooks_t dst,
			   assuan_system_hooks_t src)

{
  memset (dst, '\0', sizeof (*dst));

  dst->version = ASSUAN_SYSTEM_HOOKS_VERSION;
  if (src->version >= 1)
    {
      dst->usleep = src->usleep;
      dst->pipe = src->pipe;
      dst->close = src->close;
      dst->read = src->read;
      dst->write = src->write;
      dst->sendmsg = src->sendmsg;
      dst->recvmsg = src->recvmsg;
      dst->spawn = src->spawn;
      dst->waitpid = src->waitpid;
      dst->socketpair = src->socketpair;
    }
  if (src->version > 1)


    ;
}
