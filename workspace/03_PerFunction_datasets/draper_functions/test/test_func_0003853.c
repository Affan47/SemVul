clock_update_if_needed()
{
	int	diff;

	diff = g_clk_next_vbl_update - g_vbl_count;
	if(diff < 0 || diff > 60) {

		update_cur_time();
	}
}
