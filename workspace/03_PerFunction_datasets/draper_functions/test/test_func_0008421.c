pcap_setfilter_linux_common(pcap_t *handle, struct bpf_program *filter,
    int is_mmapped)
{
#ifdef SO_ATTACH_FILTER
	struct sock_fprog	fcode;
	int			can_filter_in_kernel;
	int			err = 0;
#endif

	if (!handle)
		return -1;
	if (!filter) {
	        strncpy(handle->errbuf, "setfilter: No filter specified",
			PCAP_ERRBUF_SIZE);
		return -1;
	}


	if (install_bpf_program(handle, filter) < 0)

		return -1;


	handle->md.use_bpf = 0;


#ifdef SO_ATTACH_FILTER
#ifdef USHRT_MAX
	if (handle->fcode.bf_len > USHRT_MAX) {


		fprintf(stderr, "Warning: Filter too complex for kernel\n");
		fcode.len = 0;
		fcode.filter = NULL;
		can_filter_in_kernel = 0;
	} else
#endif
	{


		switch (fix_program(handle, &fcode, is_mmapped)) {

		case -1:
		default:


			return -1;

		case 0:


			can_filter_in_kernel = 0;
			break;

		case 1:


			can_filter_in_kernel = 1;
			break;
		}
	}


	if (can_filter_in_kernel) {
		if ((err = set_kernel_filter(handle, &fcode)) == 0)
		{

			handle->md.use_bpf = 1;
		}
		else if (err == -1)
		{


			if (errno != ENOPROTOOPT && errno != EOPNOTSUPP) {
				fprintf(stderr,
				    "Warning: Kernel filter failed: %s\n",
					pcap_strerror(errno));
			}
		}
	}


	if (!handle->md.use_bpf)
		reset_kernel_filter(handle);


	if (fcode.filter != NULL)
		free(fcode.filter);

	if (err == -2)

		return -1;
#endif

	return 0;
}
