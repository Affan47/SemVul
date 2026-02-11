vas_write(void *buf_in, size_t count)
{
	u_long len, offset, buf, va;

	if(vas_version < 2)
		return vas_write_v1(buf_in, count);

	if(count != sizeof(u_long)) {
		printf("count %d not %d\n", (int)count, (int)sizeof(u_long));
		return -1;
	}
	va = vas_base_va;
	if(!find_data(va, &buf, &len, &offset))
	   *(u_long *)(buf+offset) = *(u_long *)buf_in;

	vas_base_va += count;
	return count;
}
