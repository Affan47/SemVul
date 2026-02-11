ps_bufferattr_setflags(ps_bufferattr_t *attr, ps_flags_t flags)
{
	if (attr == NULL)
		return EINVAL;

	if ((flags & PS_BUFFER_READY) | (flags & PS_BUFFER_CANCELLED))
		return EINVAL;

#ifndef __PS_SHM
	if (flags & PS_BUFFER_PSHARED)
		return ENOTSUP;
#endif

#ifndef __PS_STATS
	if (flags & PS_BUFFFER_STATS)
		return ENOTSUP;
#endif

	attr->flags = flags;

	return 0;
}
