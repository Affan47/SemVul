Bindable_GetStack(GF_Node *bindable)
{
	void *st;
	if (!bindable) return 0;
	st = gf_node_get_private(bindable);
	switch (gf_node_get_tag(bindable)) {
	case TAG_MPEG4_Background2D: return ((Background2DStack*)st)->reg_stacks;
	case TAG_MPEG4_Viewport:
	case TAG_MPEG4_NavigationInfo:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_NavigationInfo:
#endif
		return ((ViewStack*)st)->reg_stacks;
#ifndef GPAC_DISABLE_3D
	case TAG_MPEG4_Background:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Background:
#endif
		return ((BackgroundStack*)st)->reg_stacks;
	case TAG_MPEG4_Viewpoint:
	case TAG_MPEG4_Fog:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Viewpoint:
	case TAG_X3D_Fog:
#endif
		return ((ViewStack*)st)->reg_stacks;
#endif
	default: return NULL;
	}
}
