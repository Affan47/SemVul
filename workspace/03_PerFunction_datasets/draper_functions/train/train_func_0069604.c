stream_int_update_conn(struct stream_interface *si)
{
	struct channel *ib = si->ib;
	struct channel *ob = si->ob;
	struct connection *conn = __objt_conn(si->end);


	if (!(ib->flags & CF_SHUTR)) {

		if ((ib->flags & CF_DONT_READ) || channel_full(ib)) {

			if (!(si->flags & SI_FL_WAIT_ROOM)) {
				if (!(ib->flags & CF_DONT_READ))
					si->flags |= SI_FL_WAIT_ROOM;
				conn_data_stop_recv(conn);
				ib->rex = TICK_ETERNITY;
			}
		}
		else {


			si->flags &= ~SI_FL_WAIT_ROOM;
			conn_data_want_recv(conn);
			if (!(ib->flags & (CF_READ_NOEXP|CF_DONT_READ)) && !tick_isset(ib->rex))
				ib->rex = tick_add_ifset(now_ms, ib->rto);
		}
	}


	if (!(ob->flags & CF_SHUTW)) {

		if (channel_is_empty(ob)) {

			if (!(si->flags & SI_FL_WAIT_DATA)) {
				if ((ob->flags & CF_SHUTW_NOW) == 0)
					si->flags |= SI_FL_WAIT_DATA;
				conn_data_stop_send(conn);
				ob->wex = TICK_ETERNITY;
			}
		}
		else {


			si->flags &= ~SI_FL_WAIT_DATA;
			conn_data_want_send(conn);
			if (!tick_isset(ob->wex)) {
				ob->wex = tick_add_ifset(now_ms, ob->wto);
				if (tick_isset(ib->rex) && !(si->flags & SI_FL_INDEP_STR)) {


					ib->rex = tick_add_ifset(now_ms, ib->rto);
				}
			}
		}
	}
}
