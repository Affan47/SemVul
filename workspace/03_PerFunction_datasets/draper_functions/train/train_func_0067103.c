HPDF_3DView_SetPerspectiveProjection(HPDF_Dict view, HPDF_REAL fov)
{
	HPDF_STATUS ret = HPDF_OK;
	HPDF_Dict projection;

	HPDF_PTRACE ((" HPDF_3DView_SetPerspectiveProjection\n"));

	if (view == NULL || fov < 0 || fov > 180) {
		return HPDF_INVALID_U3D_DATA;
	}

	projection = HPDF_Dict_New (view->mmgr);
	if (!projection) {
		return HPDF_Error_GetCode (view->error);
	}

	ret = HPDF_Dict_AddName (projection, "Subtype", "P");
	if (ret != HPDF_OK) {
		HPDF_Dict_Free (projection);
		return ret;
	}

	ret = HPDF_Dict_AddName (projection, "PS", "Min");
	if (ret != HPDF_OK) {
		HPDF_Dict_Free (projection);
		return ret;
	}

	ret = HPDF_Dict_AddReal (projection, "FOV", fov);
	if (ret != HPDF_OK) {
		HPDF_Dict_Free (projection);
		return ret;
	}

	ret = HPDF_Dict_Add (view, "P", projection);
	if (ret != HPDF_OK) {
		HPDF_Dict_Free (projection);
		return ret;
	}
	return ret;
}
