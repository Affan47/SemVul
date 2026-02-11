closeAll()
{
	while (!work_areas_.empty())

		(*work_areas_.begin())->close();
}
