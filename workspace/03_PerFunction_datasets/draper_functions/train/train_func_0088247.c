usb_kick(usb_handle *h)
{
    D("[ kicking %p (fd = %d) ]\n", h, h->desc);
    adb_mutex_lock(&h->lock);
    if(h->dead == 0) {
        h->dead = 1;

        if (h->writeable) {


            if (h->reaper_thread) {
                pthread_kill(h->reaper_thread, SIGALRM);
            }


            ioctl(h->desc, USBDEVFS_DISCARDURB, &h->urb_in);
            ioctl(h->desc, USBDEVFS_DISCARDURB, &h->urb_out);
            h->urb_in.status = -ENODEV;
            h->urb_out.status = -ENODEV;
            h->urb_in_busy = 0;
            h->urb_out_busy = 0;
            adb_cond_broadcast(&h->notify);
        } else {
            unregister_usb_transport(h);
        }
    }
    adb_mutex_unlock(&h->lock);
}
