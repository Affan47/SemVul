solar_power ()
{
    int pwr = 0;
    for (int p = 0; p < parts.size(); p++)
        if (part_flag(p, vpf_solar_panel) && parts[p].hp > 0)
            pwr += part_info(p).power;
    return pwr;
}
