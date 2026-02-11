ShowGenericButtonFromList(int ButtonIndex)
{
	struct mouse_press_button *btn;


	if ((ButtonIndex >= MAX_MOUSE_PRESS_BUTTONS) || (ButtonIndex < 0)) {
		ErrorMessage(__FUNCTION__, "Request to display button index %d could not be fulfilled: the\n\
				button index given exceeds the number of buttons defined in FreedroidRPG.", PLEASE_INFORM, IS_WARNING_ONLY, ButtonIndex);
		return;
	}

	btn = &AllMousePressButtons[ButtonIndex];


	if (!strcmp(AllMousePressButtons[ButtonIndex].button_image_file_name, "THIS_DOESNT_NEED_BLITTING")) {
		return;
	}


	float scale_x = 1.0, scale_y = 1.0;
	if (btn->scale_this_button) {
		scale_x = ((float)GameConfig.screen_width) / 640.0;
		scale_y = ((float)GameConfig.screen_height) / 480.0;
	}


	struct image *img = &btn->button_image;
	if (!image_loaded(img)) {
		load_image(img, btn->button_image_file_name, FALSE);


		if (!btn->button_rect.w) {
			btn->button_rect.w = img->w;
		}

		if (!btn->button_rect.h) {
			btn->button_rect.h = img->h;
		}
	}

	display_image_on_screen(img, AllMousePressButtons[ButtonIndex].button_rect.x * scale_x, AllMousePressButtons[ButtonIndex].button_rect.y * scale_y, set_image_transformation(scale_x, scale_y, 1.0, 1.0, 1.0, 1.0, 0));
}
