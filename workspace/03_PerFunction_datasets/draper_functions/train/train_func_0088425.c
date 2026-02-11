rendering_set_quality(rendering_t * rendering, rendering_quality_t quality) {

  gdouble max_ray_opacity, min_voxel_opacity;

  rendering->need_rerender = TRUE;


  switch (quality) {
  case HIGH:
    max_ray_opacity = 0.99;
    min_voxel_opacity = 0.01;
    break;
    break;
  case FAST:
    max_ray_opacity = 0.95;
    min_voxel_opacity = 0.05;
    break;
  case FASTEST:
    max_ray_opacity = 0.9;
    min_voxel_opacity = 0.1;
    break;
  case HIGHEST:
  default:
    max_ray_opacity = 1.0;
    min_voxel_opacity = 0.0;
    break;
  }


  if (vpSetd(rendering->vpc, VP_MAX_RAY_OPACITY, max_ray_opacity) != VP_OK){
    g_warning(_("Error Setting Rendering Max Ray Opacity (%s): %s"),
	      rendering->name, vpGetErrorString(vpGetError(rendering->vpc)));
  }


  if (vpSetd(rendering->vpc, VP_MIN_VOXEL_OPACITY, min_voxel_opacity) != VP_OK) {
    g_warning(_("Error Setting the Min Voxel Opacity (%s): %s"),
	      rendering->name, vpGetErrorString(vpGetError(rendering->vpc)));
  }

  rendering->need_reclassify = TRUE;

  return;
}
