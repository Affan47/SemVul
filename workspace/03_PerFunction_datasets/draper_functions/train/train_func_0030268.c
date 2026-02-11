bound_check_x(short &paraX)
{
	if(paraX<0)
		paraX = 0;
	else if(paraX>=MAX_WORLD_X_LOC-1)
		paraX = MAX_WORLD_X_LOC-1;
}
