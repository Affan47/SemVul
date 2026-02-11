N_copy_gradient_field_3d(N_gradient_field_3d * source,
			 N_gradient_field_3d * target)
{
    G_debug(3, "N_copy_gradient_field_3d: copy N_gradient_field_3d");

    if (!source || !target)
	return 0;

    N_copy_array_3d(source->x_array, target->x_array);
    N_copy_array_3d(source->y_array, target->y_array);
    N_copy_array_3d(source->z_array, target->z_array);

    return 1;
}
