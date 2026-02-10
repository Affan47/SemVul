reset_trig_time()
{
	if (!auto_rate)
		auto_rate = 1;
	auto_trig_time = mnow() + 300 / (1 + auto_rate);
}
