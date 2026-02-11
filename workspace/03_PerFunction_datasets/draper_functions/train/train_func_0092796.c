showEvent(QShowEvent*)
{
    setRide(_ride);
    setFilter(filters);
    resizeEvent(NULL);
}
