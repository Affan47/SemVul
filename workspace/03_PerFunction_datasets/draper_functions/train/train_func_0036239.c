adjust_Q_list(int i)
{
	while (last_Qs.size() > 3)
		last_Qs.pop_front();

	while (last_Qs.size() > 0 && i--)
		last_Qs.pop_front();
}
