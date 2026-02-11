apple_fudge()
{
	EFI_GUID UGAProtocol = UGA_DRAW_PROTOCOL;
	EFI_GUID ConsoleProtocol = CONSOLE_CONTROL_PROTOCOL;
	EFI_UGA_DRAW_INTERFACE *uga_interface = 0;
	EFI_CONSOLE_CONTROL_INTERFACE *console_interface = 0;
	EFI_CONSOLE_CONTROL_SCREEN_MODE current_mode;
	UINT32 horiz, vert, depth, refresh;

	console_interface = get_protocol_handler(ConsoleProtocol);

	if (console_interface) {
		console_interface->GetMode(console_interface, &current_mode, NULL, NULL);

		if (current_mode == EfiConsoleControlScreenGraphics)
			console_interface->SetMode(console_interface, EfiConsoleControlScreenText);

		free (console_interface);
	} else
		ERR_PRT((L"Unable to find console interface\n"));


	uga_interface = get_protocol_handler(UGAProtocol);

	if (uga_interface) {
		uga_interface->GetMode(uga_interface, &horiz, &vert, &depth, &refresh);

		free (uga_interface);
	} else
		ERR_PRT((L"Unable to find UGA interface\n"));

	apple_fudge_cmdline = alloc(76, EfiLoaderData);

	SPrint(apple_fudge_cmdline, 76, L"video=imacfb:height=%d,width=%d", vert, horiz);

#ifdef CONFIG_ia32
	ia32_set_legacy_free_boot(1);
#endif

	return 0;
}
