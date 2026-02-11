x_output_page(gx_device * dev, int num_copies, int flush)
{
    gx_device_X *xdev = (gx_device_X *) dev;

    x_sync(dev);


    if (xdev->ghostview) {
        XEvent event;

        gdev_x_send_event(xdev, xdev->PAGE);
        XNextEvent(xdev->dpy, &event);
        while (event.type != ClientMessage ||
               event.xclient.message_type != xdev->NEXT) {
            XNextEvent(xdev->dpy, &event);
        }
    }
    return gx_finish_output_page(dev, num_copies, flush);
}
