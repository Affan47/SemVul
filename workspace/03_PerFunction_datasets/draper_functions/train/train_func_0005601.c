poll_fsb_p4(void) {

	ulong fsb, idetect;
	float coef = getP4PMmultiplier();
	char *name;
	int col,temp;

	fsb = ((extclock /1000) / coef);


	pci_conf_read( 0, 0, 0, 0x02, 2, &idetect);
	if (idetect == 0x2540 || idetect == 0x254C)
	{
		print_cpu_line(fsb, fsb, 1);
	} else {

		col = COL_SPEC;
		cprint(LINE_CPU, col, "Chipset:               ");
		col += 9;

		name = controllers[ctrl.index].name;
		cprint(LINE_CPU, col, name);

		temp = 20;
		while(name[temp - 20] != '\0') {
			col++;
			temp++;
		}

		if(temp < 36){
			cprint(LINE_CPU, col +1, "- FSB : ");
			col += 9;
			dprint(LINE_CPU, col, fsb, 3,0);
			col += 3;
		}

	}
}
