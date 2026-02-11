amitk_canvas_update_target(AmitkCanvas * canvas, AmitkCanvasTargetAction action,
			       AmitkPoint center, amide_real_t thickness) {

  g_return_if_fail(AMITK_IS_CANVAS(canvas));
  canvas->next_target_action = action;
  canvas->next_target_center = center;
  canvas->next_target_thickness = thickness;
  canvas_add_update(canvas, UPDATE_TARGET);

  return;
}
