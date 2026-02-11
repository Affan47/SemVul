mui_x(struct fpga_model *model, int x)
{
	int y, i;

	RC_CHECK(model);
	for (y = TOP_FIRST_REGULAR; y <= model->y_height - BOT_LAST_REGULAR_O; y++) {
		if ((i = find_mui_pos(model, y)) != -1) {

			{ struct w_net_i n = { .wire = CLK0, .wire_inc = 1, .num_yx = 3,
				{{ .y = y, .x = x },
				 { .y = y, .x = x+1 },
				 { .y = model->die->mui_pos[i]+1, .x = x+2 }}};
			add_conn_net_i(model, &n);
			n.wire = SR0;
			add_conn_net_i(model, &n);
			n.wire = LOGICIN_B0;
			n.wire_inc = LOGICIN_HIGHEST;
			add_conn_net_i(model, &n); }


			{ struct w_net_i n = { .wire = LOGICOUT_B0, .wire_inc = LOGICOUT_HIGHEST, .num_yx = 2,
				{{ .y = y, .x = x+1 }}};
			n.yx[1].y = y;
			n.yx[1].x = x;
			add_conn_net_i(model, &n);
			n.yx[1].y = model->die->mui_pos[i]+1;
			n.yx[1].x = x+2;
			add_conn_net_i(model, &n); }
		}
	}
	RC_RETURN(model);
}
