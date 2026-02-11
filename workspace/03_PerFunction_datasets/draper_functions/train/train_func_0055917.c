save_keys(void)
{
	EFI_HANDLE vol;
	CHAR16 *volname;

	simple_volume_selector((CHAR16 *[]) {
			L"Save Keys",
			L"",
			L"Select a disk Volume to save all the key files to",
			L"Key files will be saved in the top level directory",
			L"",
			L"Note: For USB volumes, some UEFI implementations aren't",
			L"very good at hotplug, so you may have to boot with the USB",
			L"USB device already plugged in to see the volume",
			NULL
		}, &volname, &vol);

	if (!volname)
		return;
	FreePool(volname);

	CHAR16 *title[10], buf[8000];
	int i, t_c = 0, b_c = 0;

	title[t_c++] = L"Results of Saving Keys";
	title[t_c++] = L"";

	for (i = 0; i < MAX_KEYS; i++) {
		save_key_internal(i, vol, &buf[b_c]);
		title[t_c++] = &buf[b_c];
		b_c += StrLen(&buf[b_c]) + 1;
	}
	title[t_c] = NULL;
	console_alertbox(title);
}
