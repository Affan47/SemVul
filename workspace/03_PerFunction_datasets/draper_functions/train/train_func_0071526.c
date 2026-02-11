amitk_study_set_view_center(AmitkStudy * study, const AmitkPoint new_center) {

  AmitkPoint temp;
  g_return_if_fail(AMITK_IS_STUDY(study));

  temp = amitk_space_b2s(AMITK_SPACE(study), new_center);

  if (!POINT_EQUAL(study->view_center, temp)) {
    study->view_center = temp;
    g_signal_emit(G_OBJECT(study), study_signals[VIEW_CENTER_CHANGED], 0);
  }

  return;
}
