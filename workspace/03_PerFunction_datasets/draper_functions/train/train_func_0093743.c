build_vident(void)
{
	struct utsname uts;

	vident = VSB_new_auto();
	AN(vident);
	if (!uname(&uts)) {
		VSB_printf(vident, ",%s", uts.sysname);
		VSB_printf(vident, ",%s", uts.release);
		VSB_printf(vident, ",%s", uts.machine);
	}
}
