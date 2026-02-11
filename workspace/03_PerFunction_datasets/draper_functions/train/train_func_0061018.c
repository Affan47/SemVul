gf_sg_vrml_field_pointer_del(void *field, u32 FieldType)
{
	GF_Node *node;

	switch (FieldType) {
	case GF_SG_VRML_SFBOOL:
	case GF_SG_VRML_SFFLOAT:
	case GF_SG_VRML_SFDOUBLE:
	case GF_SG_VRML_SFTIME:
	case GF_SG_VRML_SFINT32:
	case GF_SG_VRML_SFVEC3F:
	case GF_SG_VRML_SFVEC3D:
	case GF_SG_VRML_SFVEC2F:
	case GF_SG_VRML_SFVEC2D:
	case GF_SG_VRML_SFCOLOR:
	case GF_SG_VRML_SFCOLORRGBA:
	case GF_SG_VRML_SFROTATION:
	case GF_SG_VRML_SFATTRREF:
		break;
	case GF_SG_VRML_SFSTRING:
		if ( ((SFString *)field)->buffer) gf_free(((SFString *)field)->buffer);
		break;
	case GF_SG_VRML_SFIMAGE:
		gf_sg_sfimage_del(* ((SFImage *)field));
		break;

	case GF_SG_VRML_SFNODE:
		node = *(GF_Node **) field;
		if (node) gf_node_del(node);
		return;
	case GF_SG_VRML_SFCOMMANDBUFFER:
		gf_sg_sfcommand_del(*(SFCommandBuffer *)field);
		break;

	case GF_SG_VRML_MFBOOL:
		gf_sg_mfbool_del( * ((MFBool *) field));
		break;
	case GF_SG_VRML_MFFLOAT:
		gf_sg_mffloat_del( * ((MFFloat *) field));
		break;
	case GF_SG_VRML_MFDOUBLE:
		gf_sg_mfdouble_del( * ((MFDouble *) field));
		break;
	case GF_SG_VRML_MFTIME:
		gf_sg_mftime_del( * ((MFTime *)field));
		break;
	case GF_SG_VRML_MFINT32:
		gf_sg_mfint32_del( * ((MFInt32 *)field));
		break;
	case GF_SG_VRML_MFSTRING:
		gf_sg_mfstring_del( *((MFString *)field));
		break;
	case GF_SG_VRML_MFVEC3F:
		gf_sg_mfvec3f_del( * ((MFVec3f *)field));
		break;
	case GF_SG_VRML_MFVEC2F:
		gf_sg_mfvec2f_del( * ((MFVec2f *)field));
		break;
	case GF_SG_VRML_MFVEC3D:
		gf_sg_mfvec3d_del( * ((MFVec3d *)field));
		break;
	case GF_SG_VRML_MFVEC2D:
		gf_sg_mfvec2d_del( * ((MFVec2d *)field));
		break;
	case GF_SG_VRML_MFCOLOR:
		gf_sg_mfcolor_del( * ((MFColor *)field));
		break;
	case GF_SG_VRML_MFCOLORRGBA:
		gf_sg_mfcolor_rgba_del( * ((MFColorRGBA *)field));
		break;
	case GF_SG_VRML_MFROTATION:
	case GF_SG_VRML_MFVEC4F:
		gf_sg_mfrotation_del( * ((MFRotation *)field));
		break;
	case GF_SG_VRML_SFURL:
		gf_sg_sfurl_del( * ((SFURL *) field));
		break;
	case GF_SG_VRML_MFURL:
		gf_sg_mfurl_del( * ((MFURL *) field));
		break;
	case GF_SG_VRML_MFATTRREF:
		gf_sg_mfattrref_del( * ((MFAttrRef *) field));
		break;

	case GF_SG_VRML_MFNODE:
		assert(0);
		return;
	case GF_SG_VRML_MFSCRIPT:
		gf_sg_mfscript_del( * ((MFScript *) field));
		break;

	default:
		assert(0);
		return;
	}

	gf_free(field);
}
