suggest_laptop_mode(void)
{
	FILE *file;
	int i;
	char buffer[1024];


	file = fopen("/proc/acpi/ac_adapter/AC/state", "r");
	if (!file)
		return;
	memset(buffer, 0, 1024);
	if (!fgets(buffer, 1023, file)) {
		fclose(file);
		return;
	}
	fclose(file);
	if (strstr(buffer, "on-line") != NULL)
		return;


	file = fopen("/proc/sys/vm/laptop_mode", "r");
	if (!file)
		return;
	memset(buffer, 0, 1024);
	if (!fgets(buffer, 1023, file)) {
		fclose(file);
		return;
	}
	i = strtoul(buffer, NULL, 10);
	if (i<1) {
		add_suggestion( _("Suggestion: Enable laptop-mode by executing the following command:\n"
		 	"   echo 5 > /proc/sys/vm/laptop_mode \n"), 15, 'L', _(" L - enable Laptop mode "), set_laptop_mode);
	}
	fclose(file);
}
