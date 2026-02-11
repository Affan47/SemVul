hud_squadmsg_wing_command()
{
	int k;
	wing *wingp;
	int default_orders, i, orders;


	wingp = &Wings[Msg_instance];


	default_orders = 0;
	for ( i = 0; i < wingp->current_count; i++ ) {
		orders = ship_get_default_orders_accepted( &Ship_info[Ships[wingp->ship_index[i]].ship_info_index] );
		default_orders |= orders;
	}
	default_orders &= ~CAPTURE_TARGET_ITEM;

	Num_menu_items = 0;
	orders = Ships[wingp->ship_index[0]].orders_accepted;
	for ( i = 0; i < NUM_COMM_ORDER_ITEMS; i++ ) {


		if ( default_orders & Comm_orders[i].item ) {
			Assert ( Num_menu_items < MAX_MENU_ITEMS );
			strcpy_s(MsgItems[Num_menu_items].text, Comm_orders[i].name);
			MsgItems[Num_menu_items].instance = Comm_orders[i].item;
			MsgItems[Num_menu_items].active = 0;


			if ( orders & Comm_orders[i].item )
				MsgItems[Num_menu_items].active = 1;


			if ( !hud_squadmsg_is_target_order_valid(i, 0) )
				MsgItems[Num_menu_items].active = 0;

			Num_menu_items++;
		}
	}


	strcpy_s(Squad_msg_title, XSTR( "What Command", 321) );
	k = hud_squadmsg_get_key();
	if ( k != -1 ) {


			hud_squadmsg_send_wing_command(Msg_instance, MsgItems[k].instance, 1);

		hud_squadmsg_toggle();
	}
}
