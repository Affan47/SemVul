_e2_task_backend_overwrite (VPATH *dest, VPATH *replace)
{
	E2_ERR_DECLARE
	if (!_e2_task_backend_delete (dest E2_ERR_PTR()))
	{


		e2_fs_error_local (_("Cannot delete existing %s"), dest E2_ERR_MSGL());
		E2_ERR_CLEAR
		return FALSE;
	}
	else
		e2_fs_rename (replace, dest E2_ERR_NONE());

	return TRUE;
}
