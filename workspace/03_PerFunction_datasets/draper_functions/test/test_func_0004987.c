check_shellsize()
{
    if (Rows < min_rows())
	Rows = min_rows();
    limit_screen_size();
}
