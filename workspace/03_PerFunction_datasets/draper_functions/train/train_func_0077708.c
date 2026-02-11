check_current_patch_level(u32 *rev, bool early)
{
	u32 lvl, dummy, i;
	bool ret = false;
	u32 *levels;

	native_rdmsr(MSR_AMD64_PATCH_LEVEL, lvl, dummy);

	if (IS_ENABLED(CONFIG_X86_32) && early)
		levels = (u32 *)__pa_nodebug(&final_levels);
	else
		levels = final_levels;

	for (i = 0; levels[i]; i++) {
		if (lvl == levels[i]) {
			lvl = 0;
			ret = true;
			break;
		}
	}

	if (rev)
		*rev = lvl;

	return ret;
}
