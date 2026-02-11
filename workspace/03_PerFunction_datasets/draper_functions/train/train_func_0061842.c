rio_update_route_tables(struct rio_net *net)
{
	struct rio_dev *rdev, *swrdev;
	struct rio_switch *rswitch;
	u8 sport;
	u16 destid;

	list_for_each_entry(rdev, &net->devices, net_list) {

		destid = rdev->destid;

		list_for_each_entry(rswitch, &net->switches, node) {

			if (rio_is_switch(rdev)	&& (rdev->rswitch == rswitch))
				continue;

			if (RIO_INVALID_ROUTE == rswitch->route_table[destid]) {
				swrdev = sw_to_rio_dev(rswitch);


				if (swrdev->destid == destid)
					continue;

				sport = RIO_GET_PORT_NUM(swrdev->swpinfo);

				rio_route_add_entry(swrdev, RIO_GLOBAL_TABLE,
						    destid, sport, 0);
				rswitch->route_table[destid] = sport;
			}
		}
	}
}
