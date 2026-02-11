initialize_transfer_screen(void)
{
	int iface_nmbr;


	sock_send_string(sock, "screen_add NT\n");


	sock_send_string(sock, "screen_set NT name {Transfer}\n");


	sock_send_string(sock, "widget_add NT title title\n");

	if ((iface_count == 1) && (lcd_hgt >= 4)) {

		sock_printf(sock, "widget_set NT title {Transfer: %s}\n", iface[0].alias);


		sock_send_string(sock, "widget_add NT dl string\n");
		sock_send_string(sock, "widget_set NT dl 1 2 {DL:}\n");
		sock_send_string(sock, "widget_add NT ul string\n");
		sock_send_string(sock, "widget_set NT ul 1 3 {UL:}\n");
		sock_send_string(sock, "widget_add NT total string\n");
		sock_send_string(sock, "widget_set NT total 1 4 {Total:}\n");
	}
	else {

		sock_send_string(sock, "widget_set NT title {Net Transfer (bytes)}\n");
		sock_send_string(sock, "widget_add NT f frame\n");


		sock_printf(sock, "widget_set NT f 1 2 %d %d %d %d v 16\n",
				lcd_wid, lcd_hgt, lcd_wid, iface_count,

				((lcd_hgt >= 4) ? 8 : 16));

		for (iface_nmbr = 0; iface_nmbr < iface_count; iface_nmbr++) {
			sock_printf(sock, "widget_add NT i%1d string -in f\n", iface_nmbr);
			sock_printf(sock, "widget_set NT i%1d 1 %1d {%5.5s NA (never)}\n",
					iface_nmbr, iface_nmbr+1, iface[iface_nmbr].alias);
		}
	}
}
