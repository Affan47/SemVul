amdgpu_is_uvd_state(u32 class, u32 class2)
{
	if (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		return true;
	if (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		return true;
	if (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		return true;
	return false;
}
