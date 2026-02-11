checkDisplayStatus(struct display *d)
{
    if ((d->displayType & d_origin) == dFromFile && !d->stillThere)
        stopDisplay(d);
    else if (d->status == notRunning)
        if (loadDisplayResources(d) < 0) {
            logError("Unable to read configuration for display %s; "
                     "stopping it.\n", d->name);
            stopDisplay(d);
            return;
        }
}
