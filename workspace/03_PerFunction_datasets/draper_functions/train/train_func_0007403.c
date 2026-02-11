gtt_project_set_estimated_start (GttProject *proj, time_t r)
{
	if (!proj) return;
	proj->estimated_start = r;
	proj_modified (proj);
}
