gf_sg_vrml_node_init(GF_Node *node)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_ColorInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_ColorInterpolator:
#endif
		return InitColorInterpolator((M_ColorInterpolator *)node);
	case TAG_MPEG4_CoordinateInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_CoordinateInterpolator:
#endif
		return InitCoordinateInterpolator((M_CoordinateInterpolator *)node);
	case TAG_MPEG4_CoordinateInterpolator2D:
		return InitCoordinateInterpolator2D((M_CoordinateInterpolator2D *)node);
	case TAG_MPEG4_NormalInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_NormalInterpolator:
#endif
		return InitNormalInterpolator((M_NormalInterpolator*)node);
	case TAG_MPEG4_OrientationInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_OrientationInterpolator:
#endif
		return InitOrientationInterpolator((M_OrientationInterpolator*)node);
	case TAG_MPEG4_PositionInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_PositionInterpolator:
#endif
		return InitPositionInterpolator((M_PositionInterpolator *)node);
	case TAG_MPEG4_PositionInterpolator2D:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_PositionInterpolator2D:
#endif
		return InitPositionInterpolator2D((M_PositionInterpolator2D *)node);
	case TAG_MPEG4_ScalarInterpolator:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_ScalarInterpolator:
#endif
		return InitScalarInterpolator((M_ScalarInterpolator *)node);
	case TAG_MPEG4_Valuator:
		return InitValuator((M_Valuator *)node);
	case TAG_MPEG4_PositionAnimator:
		PA_Init(node); return 1;
	case TAG_MPEG4_PositionAnimator2D:
		PA2D_Init(node); return 1;
	case TAG_MPEG4_ScalarAnimator:
		SA_Init(node); return 1;
	case TAG_MPEG4_PositionInterpolator4D:
		return InitPositionInterpolator4D((M_PositionInterpolator4D *)node);
	case TAG_MPEG4_CoordinateInterpolator4D:
		return InitCoordinateInterpolator4D((M_CoordinateInterpolator4D *)node);
	case TAG_MPEG4_Script:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Script:
#endif
		return 1;

#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_BooleanFilter: InitBooleanFilter(node); return 1;
	case TAG_X3D_BooleanSequencer: InitBooleanSequencer(node); return 1;
	case TAG_X3D_BooleanToggle: InitBooleanToggle(node); return 1;
	case TAG_X3D_BooleanTrigger: InitBooleanTrigger(node); return 1;
	case TAG_X3D_IntegerSequencer: InitIntegerSequencer(node); return 1;
	case TAG_X3D_IntegerTrigger: InitIntegerTrigger(node); return 1;
	case TAG_X3D_TimeTrigger: InitTimeTrigger(node); return 1;
#endif
	}
	return 0;
}
