get(guint &new_interval)
{
    const unsigned config_interval = ProcmanApp::get()->config.update_interval;

    g_assert(this->interval >= config_interval);

    if (not this->active)
        return false;


    const unsigned pcpu = this->get_own_cpu_usage();


    if (pcpu > PCPU_HI && this->last_pcpu > PCPU_HI)
        new_interval = this->interval * 11 / 10;
    else if (this->interval != config_interval && pcpu < PCPU_LO && this->last_pcpu < PCPU_LO)
        new_interval = this->interval * 9 / 10;
    else
        new_interval = this->interval;

    new_interval = CLAMP(new_interval, config_interval, config_interval * 2);
    new_interval = CLAMP(new_interval, MIN_UPDATE_INTERVAL, MAX_UPDATE_INTERVAL);

    bool changed = this->interval != new_interval;

    if (changed)
        this->interval = new_interval;

    this->last_pcpu = pcpu;


    if (changed) {
        procman_debug("CPU usage is %3u%%, changed refresh_interval to %u (config %u)",
                      this->last_pcpu,
                      this->interval,
                      config_interval);
    }

    g_assert(this->interval == new_interval);
    g_assert(this->interval >= config_interval);

    return changed;
}
