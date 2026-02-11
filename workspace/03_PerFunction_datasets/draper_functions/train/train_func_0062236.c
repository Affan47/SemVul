do_capset(int cap_ordinal)
{
	struct __user_cap_header_struct hdr;
	struct __user_cap_data_struct caps[2];


	hdr.version = _LINUX_CAPABILITY_VERSION_3;
	hdr.pid = getpid();
	if (capget(&hdr, caps)) {
		perror("capget()");
		exit(1);
	}


	if (cap_ordinal < 32)
		caps[0].inheritable &= ~(1U << cap_ordinal);
	else
		caps[1].inheritable &= ~(1U << (cap_ordinal - 32));


	hdr.version = _LINUX_CAPABILITY_VERSION_3;
	hdr.pid = getpid();
	if (capset(&hdr, caps))
		fail("Couldn't drop the capability \"%s\"\n",
		     capabilities[cap_ordinal].cap_name);
}
