render_find_selected_objects_and_refresh_display (gint activeFileIndex, gboolean eraseOldSelection){

	if ((eraseOldSelection)&&(screen.selectionInfo.selectedNodeArray->len))
		g_array_remove_range (screen.selectionInfo.selectedNodeArray, 0,
			screen.selectionInfo.selectedNodeArray->len);


	if (!render_create_cairo_buffer_surface())
		return;


	cairo_t *cr= cairo_create(screen.bufferSurface);
	gerbv_render_cairo_set_scale_and_translation(cr,&screenRenderInfo);
	draw_image_to_cairo_target (cr, mainProject->file[activeFileIndex]->image,
		1.0/MAX(screenRenderInfo.scaleFactorX, screenRenderInfo.scaleFactorY),
		FIND_SELECTIONS, &screen.selectionInfo, &screenRenderInfo, TRUE,
		mainProject->file[activeFileIndex]->transform, TRUE);
	cairo_destroy (cr);


	if (!screen.selectionInfo.selectedNodeArray->len)
		screen.selectionInfo.type = GERBV_SELECTION_EMPTY;

	if (screenRenderInfo.renderType <= GERBV_RENDER_TYPE_GDK_XOR){
		render_refresh_rendered_image_on_screen ();
	}
	else {
		render_selection_layer();
		render_recreate_composite_surface ();
		callbacks_force_expose_event_for_screen();
	}
}
