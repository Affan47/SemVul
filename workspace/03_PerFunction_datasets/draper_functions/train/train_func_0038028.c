setLoad(double load)
{

    if (load > 1000) load = 1000;
    if (load < 50) load = 50;

    pvars.lock();
    this->load = load;
    pvars.unlock();
}
