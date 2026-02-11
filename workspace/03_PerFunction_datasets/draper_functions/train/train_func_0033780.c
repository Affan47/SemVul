prog_fd_array_get_ptr(struct bpf_map *map, int fd)
{
	struct bpf_array *array = container_of(map, struct bpf_array, map);
	struct bpf_prog *prog = bpf_prog_get(fd);
	if (IS_ERR(prog))
		return prog;

	if (!bpf_prog_array_compatible(array, prog)) {
		bpf_prog_put(prog);
		return ERR_PTR(-EINVAL);
	}
	return prog;
}
