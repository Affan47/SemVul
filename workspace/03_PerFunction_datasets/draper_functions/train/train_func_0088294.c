gth_image_selector_set_ratio (GthImageSelector *self,
			      gboolean          use_ratio,
			      double            ratio,
			      gboolean		swap_x_and_y_to_start)
{
	int new_starting_width;

	self->priv->use_ratio = use_ratio;
	self->priv->ratio = ratio;

	if (self->priv->use_ratio) {


		if (swap_x_and_y_to_start == TRUE)
			new_starting_width = self->priv->selection.height;
		else
	       		new_starting_width = self->priv->selection.width;

		gth_image_selector_set_selection_width (self, new_starting_width);
		gth_image_selector_set_selection_height (self, self->priv->selection.height);


		if ( (swap_x_and_y_to_start == TRUE) &&
		     (self->priv->selection.width != new_starting_width))
		{
			gth_image_selector_set_selection_width (self, self->priv->selection.width);
			gth_image_selector_set_selection_height (self, self->priv->selection.height);
		}
	}
}
