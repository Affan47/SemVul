COM_Graph_close(void)
{
    if (driver->Graph_close)
	(*driver->Graph_close) ();
}
