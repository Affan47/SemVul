Nviz_resize_window(int width, int height)
{
    int ret;

    ret = 1;

    if (width < 1 || height < 1) {
	width = 20;
	height = 20;
	ret = 0;
    }

    G_debug(1, "Nviz_resize_window(): width = %d height = %d", width, height);
    GS_set_viewport(0, width, 0, height);


    GS_set_draw(GSD_BACK);
    GS_ready_draw();
    GS_alldraw_wire();
    GS_done_draw();

    return ret;
}
