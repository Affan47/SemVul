GetFontAscender() {
	return my_internaldata->FaceCache ?
	       FT_CEIL(FT_MulFix(my_internaldata->FaceCache->Face->ascender, my_internaldata->FaceCache->Face->size->metrics.y_scale)) : 0;
}
