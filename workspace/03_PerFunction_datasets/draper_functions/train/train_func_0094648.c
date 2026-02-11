ftrace_init_buffers(struct ring_buffer_per_cpu *buffers,
		ulong ring_buffer, unsigned pages)
{
	int i;
	ulong buffers_array;

	read_value(buffers_array, ring_buffer, ring_buffer, buffers);

	for (i = 0; i < nr_cpu_ids; i++) {
		if (!readmem(buffers_array + sizeof(ulong) * i, KVADDR,
				&buffers[i].kaddr, sizeof(ulong),
				"ring_buffer's cpu buffer", RETURN_ON_ERROR))
			goto out_fail;

		if (!buffers[i].kaddr)
			continue;

#define buffer_read_value(member) read_value(buffers[i].member,		\
			buffers[i].kaddr, ring_buffer_per_cpu, member)

		buffer_read_value(head_page);
		buffer_read_value(tail_page);
		buffer_read_value(commit_page);
		buffer_read_value(reader_page);
		buffer_read_value(overrun);
		buffer_read_value(entries);
		if (per_cpu_buffer_sizes) {
			buffer_read_value(nr_pages);
			pages = buffers[i].nr_pages;
		} else
			buffers[i].nr_pages = pages;

#undef buffer_read_value

		if (ftrace_init_pages(buffers + i, pages) < 0)
			goto out_fail;

		if (verbose) {
			fprintf(fp, "overrun=%lu\n", buffers[i].overrun);
			fprintf(fp, "entries=%lu\n", buffers[i].entries);
		}
	}

	return 0;

out_fail:
	ftrace_destroy_buffers(buffers);
	return -1;
}
