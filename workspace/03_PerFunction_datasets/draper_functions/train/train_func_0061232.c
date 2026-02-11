update_crop_region (GthFileToolRotate *self)
{
	if (self->priv->crop_enabled) {
		double rotation_angle;
		double crop_p1;
		double crop_p2;

		rotation_angle = gtk_adjustment_get_value (self->priv->rotation_angle_adj);
		crop_p1 = gtk_adjustment_get_value (self->priv->crop_p1_adj);
		crop_p2 = gtk_adjustment_get_value (self->priv->crop_p2_adj);
		_cairo_image_surface_rotate_get_cropping_region (self->priv->image,
								 rotation_angle,
								 crop_p1,
								 crop_p2,
								 &self->priv->crop_region);
		gth_image_rotator_set_crop_region (GTH_IMAGE_ROTATOR (self->priv->rotator), &self->priv->crop_region);
	}
	else
		gth_image_rotator_set_crop_region (GTH_IMAGE_ROTATOR (self->priv->rotator), NULL);
}
