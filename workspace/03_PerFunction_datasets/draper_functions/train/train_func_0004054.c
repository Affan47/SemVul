preloader_needs_to_load (Preloader *preloader)
{
	return ((preloader->token == preloader->self->priv->token)
		 && (preloader->file_data != NULL)
		 && ! preloader->error
		 && ! preloader->loaded);
}
