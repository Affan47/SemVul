calculate_min_max_lod(struct gl_sampler_object *samp, struct gl_texture_object *tObj,
				       unsigned *pminLod, unsigned *pmaxLod)
{
	int minLod, maxLod;


	switch (tObj->Target) {
	case GL_TEXTURE_1D:
	case GL_TEXTURE_2D:
	case GL_TEXTURE_3D:
	case GL_TEXTURE_CUBE_MAP:
		if (samp->MinFilter == GL_NEAREST || samp->MinFilter == GL_LINEAR) {


			minLod = maxLod = tObj->BaseLevel;
		} else {
			minLod = tObj->BaseLevel + (GLint)(samp->MinLod);
			minLod = MAX2(minLod, tObj->BaseLevel);
			minLod = MIN2(minLod, tObj->MaxLevel);
			maxLod = tObj->BaseLevel + (GLint)(samp->MaxLod + 0.5);
			maxLod = MIN2(maxLod, tObj->MaxLevel);
			maxLod = MIN2(maxLod, tObj->Image[0][minLod]->MaxNumLevels - 1 + minLod);
			maxLod = MAX2(maxLod, minLod);
		}
		break;
	case GL_TEXTURE_RECTANGLE_NV:
	case GL_TEXTURE_4D_SGIS:
		minLod = maxLod = 0;
		break;
	default:
		return;
	}

	radeon_print(RADEON_TEXTURE, RADEON_TRACE,
			"%s(%p) target %s, min %d, max %d.\n",
			__func__, tObj,
			_mesa_lookup_enum_by_nr(tObj->Target),
			minLod, maxLod);


	*pminLod = minLod;
	*pmaxLod = maxLod;
}
