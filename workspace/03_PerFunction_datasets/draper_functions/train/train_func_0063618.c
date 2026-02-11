f_mattrans(VALUE *vp)
{
	VALUE result;


	result.v_subtype = V_NOSUBTYPE;

	if (vp->v_type != V_MAT)
		return error_value(E_MATTRANS1);
	if (vp->v_mat->m_dim > 2)
		return error_value(E_MATTRANS2);
	result.v_type = V_MAT;
	result.v_mat = mattrans(vp->v_mat);
	return result;
}
