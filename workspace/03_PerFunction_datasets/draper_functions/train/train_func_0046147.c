mx_deform_bow_tie_texture_vflip (ClutterTexture *texture)
{
  CoglHandle material;

  material = clutter_texture_get_cogl_material (texture);

  if (material)
    {
      CoglMatrix matrix;
      cogl_matrix_init_identity (&matrix);


      cogl_matrix_scale (&matrix, 1.f, -1.f, 1.f);
      cogl_matrix_translate (&matrix, 0.f, 1.f, 0.f);

      cogl_material_set_layer_matrix (material, 0, &matrix);
    }
}
