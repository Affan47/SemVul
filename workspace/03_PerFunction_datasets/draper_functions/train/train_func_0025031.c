flash_destroy(void *data) {
  GhosdFlashData *flash = data;
  if (flash->user_render.data_destroy)
    flash->user_render.data_destroy(flash->user_render.data);
}
