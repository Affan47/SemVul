NDT_V6_GetNodeType(u32 NDT_Tag, u32 NodeTag)
{
	if(!NDT_Tag || !NodeTag) return 0;
	switch(NDT_Tag) {
	case NDT_SFWorldNode:
		return ALL_GetNodeType(SFWorldNode_V6_TypeToTag, SFWorldNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SF3DNode:
		return ALL_GetNodeType(SF3DNode_V6_TypeToTag, SF3DNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SF2DNode:
		return ALL_GetNodeType(SF2DNode_V6_TypeToTag, SF2DNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFGeometryNode:
		return ALL_GetNodeType(SFGeometryNode_V6_TypeToTag, SFGeometryNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFTextureNode:
		return ALL_GetNodeType(SFTextureNode_V6_TypeToTag, SFTextureNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFFontStyleNode:
		return ALL_GetNodeType(SFFontStyleNode_V6_TypeToTag, SFFontStyleNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFLinePropertiesNode:
		return ALL_GetNodeType(SFLinePropertiesNode_V6_TypeToTag, SFLinePropertiesNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFTextureTransformNode:
		return ALL_GetNodeType(SFTextureTransformNode_V6_TypeToTag, SFTextureTransformNode_V6_Count, NodeTag, GF_BIFS_V6);
	case NDT_SFViewportNode:
		return ALL_GetNodeType(SFViewportNode_V6_TypeToTag, SFViewportNode_V6_Count, NodeTag, GF_BIFS_V6);
	default:
		return 0;
	}
}
