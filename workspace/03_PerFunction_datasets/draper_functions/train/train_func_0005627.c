get_city_sprite(const struct city_sprite *city_sprite,
				      const struct city *pcity)
{

  int style = style_of_city(pcity);
  int num_thresholds;
  struct city_style_threshold *thresholds;
  int img_index;

  fc_assert_ret_val(style < city_sprite->num_styles, NULL);

  if (is_ocean_tile(pcity->tile)
      && city_sprite->styles[style].oceanic_num_thresholds != 0) {
    num_thresholds = city_sprite->styles[style].oceanic_num_thresholds;
    thresholds = city_sprite->styles[style].oceanic_thresholds;
  } else {
    num_thresholds = city_sprite->styles[style].land_num_thresholds;
    thresholds = city_sprite->styles[style].land_thresholds;
  }

  if (num_thresholds == 0) {
    return NULL;
  }


  img_index = get_city_bonus(pcity, EFT_CITY_IMAGE);
  img_index = CLIP(0, img_index, num_thresholds - 1);

  return thresholds[img_index].sprite;
}
