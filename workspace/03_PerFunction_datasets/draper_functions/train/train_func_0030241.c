go_path_append (GOPath *path1, GOPath const *path2)
{
	if (path2 == NULL)
		return path1;
	if (path1 == NULL)
		return go_path_copy (path2);
	go_path_interpret (path2, GO_PATH_DIRECTION_FORWARD,
			   (GOPathMoveToFunc) go_path_append_move_to,
			   (GOPathLineToFunc) go_path_append_line_to,
			   (GOPathCurveToFunc) go_path_append_curve_to,
			   (GOPathClosePathFunc) go_path_append_close, path1);
	return path1;
}
