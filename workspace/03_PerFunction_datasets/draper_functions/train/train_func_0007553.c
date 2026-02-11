gui_window_resize(WINDOW_REC *window, int width, int height)
{
	GUI_WINDOW_REC *gui;

	if (window->width == width && window->height == height)
                return;

	gui = WINDOW_GUI(window);

	irssi_set_dirty();
        WINDOW_MAIN(window)->dirty = TRUE;

        window->width = width;
	window->height = height;
        textbuffer_view_resize(gui->view, width, height);
}
