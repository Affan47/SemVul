Bindable_GetSetBind(GF_Node *bindable)
{
	if (!bindable) return 0;
	switch (gf_node_get_tag(bindable)) {
	case TAG_MPEG4_Background2D: return ((M_Background2D*)bindable)->set_bind;
	case TAG_MPEG4_Viewport: return ((M_Viewport*)bindable)->set_bind;
	case TAG_MPEG4_Background:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Background:
#endif
		return ((M_Background*)bindable)->set_bind;
	case TAG_MPEG4_NavigationInfo:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_NavigationInfo:
#endif
		return ((M_NavigationInfo*)bindable)->set_bind;
	case TAG_MPEG4_Viewpoint:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Viewpoint:
#endif
		return ((M_Viewpoint*)bindable)->set_bind;
	case TAG_MPEG4_Fog:
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Fog:
#endif
		return ((M_Fog*)bindable)->set_bind;
	default: return 0;
	}
}
