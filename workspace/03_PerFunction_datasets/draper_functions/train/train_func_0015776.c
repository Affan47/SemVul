amitk_axes_rotate_on_vector(AmitkAxes axes, AmitkPoint vector, amide_real_t theta) {
  AmitkAxis i_axis;
  for (i_axis=0;i_axis<AMITK_AXIS_NUM;i_axis++)
    axes[i_axis] = point_rotate_on_vector(axes[i_axis], vector, theta);
  return;
}
