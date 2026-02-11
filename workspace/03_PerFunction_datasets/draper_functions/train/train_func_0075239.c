print_error_description(struct kasan_access_info *info)
{
	const char *bug_type = "unknown-crash";
	u8 *shadow_addr;

	info->first_bad_addr = find_first_bad_addr(info->access_addr,
						info->access_size);

	shadow_addr = (u8 *)kasan_mem_to_shadow(info->first_bad_addr);


	if (*shadow_addr > 0 && *shadow_addr <= KASAN_SHADOW_SCALE_SIZE - 1)
		shadow_addr++;

	switch (*shadow_addr) {
	case 0 ... KASAN_SHADOW_SCALE_SIZE - 1:


		bug_type = "out-of-bounds";
		break;
	case KASAN_PAGE_REDZONE:
	case KASAN_KMALLOC_REDZONE:
		bug_type = "slab-out-of-bounds";
		break;
	case KASAN_GLOBAL_REDZONE:
		bug_type = "global-out-of-bounds";
		break;
	case KASAN_STACK_LEFT:
	case KASAN_STACK_MID:
	case KASAN_STACK_RIGHT:
	case KASAN_STACK_PARTIAL:
		bug_type = "stack-out-of-bounds";
		break;
	case KASAN_FREE_PAGE:
	case KASAN_KMALLOC_FREE:
		bug_type = "use-after-free";
		break;
	}

	pr_err("BUG: KASAN: %s in %pS at addr %p\n",
		bug_type, (void *)info->ip,
		info->access_addr);
	pr_err("%s of size %zu by task %s/%d\n",
		info->is_write ? "Write" : "Read",
		info->access_size, current->comm, task_pid_nr(current));
}
