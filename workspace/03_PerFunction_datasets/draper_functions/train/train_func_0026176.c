gf_sg_vrml_node_changed(GF_Node *node, GF_FieldInfo *field)
{
	switch (node->sgprivate->tag) {
	case TAG_ProtoNode:

		if (node->sgprivate->UserCallback) return 0;
	case TAG_MPEG4_ColorInterpolator:
	case TAG_MPEG4_CoordinateInterpolator:
	case TAG_MPEG4_CoordinateInterpolator2D:
	case TAG_MPEG4_NormalInterpolator:
	case TAG_MPEG4_OrientationInterpolator:
	case TAG_MPEG4_PositionInterpolator:
	case TAG_MPEG4_PositionInterpolator2D:
	case TAG_MPEG4_ScalarInterpolator:
	case TAG_MPEG4_Valuator:
	case TAG_MPEG4_PositionInterpolator4D:
	case TAG_MPEG4_CoordinateInterpolator4D:
	case TAG_MPEG4_Script:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_ColorInterpolator:
	case TAG_X3D_CoordinateInterpolator:
	case TAG_X3D_NormalInterpolator:
	case TAG_X3D_OrientationInterpolator:
	case TAG_X3D_PositionInterpolator:
	case TAG_X3D_ScalarInterpolator:
	case TAG_X3D_Script:
	case TAG_X3D_BooleanFilter:
	case TAG_X3D_BooleanSequencer:
	case TAG_X3D_BooleanToggle:
	case TAG_X3D_BooleanTrigger:
	case TAG_X3D_IntegerSequencer:
	case TAG_X3D_IntegerTrigger:
	case TAG_X3D_TimeTrigger:
#endif
		return 1;
	case TAG_MPEG4_PositionAnimator: PA_Modified(node, field); return 1;
	case TAG_MPEG4_PositionAnimator2D: PA2D_Modified(node, field); return 1;
	case TAG_MPEG4_ScalarAnimator: SA_Modified(node, field); return 1;
	}
	return 0;
}
