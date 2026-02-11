borg_flow_cost_stair(int y, int x, int b_stair)
{
	int cost = 255;


    borg_flow_clear();


	if (b_stair == -1) return (0);


    borg_flow_enqueue_grid(track_less_y[b_stair],track_less_x[b_stair]);


    borg_flow_spread(250, FALSE, FALSE, FALSE, b_stair, FALSE);


	cost = borg_data_cost->data[y][x];

	return (cost);
}
