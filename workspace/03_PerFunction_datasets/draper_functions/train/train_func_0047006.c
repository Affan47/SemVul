gap_morph_render_one_tween(GapMorphGlobalParams *mgpp)
{
  gint32 new_layer_id;
  gdouble total_steps;
  gdouble current_step;

  total_steps = 1.0 * 100000;
  current_step = CLAMP(mgpp->tween_mix_factor, 0.0, 1.0) * 100000;


  new_layer_id = gap_morph_render_one_of_n_tweens(mgpp, total_steps, current_step);

  return (new_layer_id);
}
