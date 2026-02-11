get_page_height (GthContactSheetCreator *self,
		 int                     page_n)
{
	return self->priv->same_size ? self->priv->page_height : self->priv->pages_height[page_n - 1];
}
