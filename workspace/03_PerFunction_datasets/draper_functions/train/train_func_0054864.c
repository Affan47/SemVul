setAntiAliased(const bool anti_alaised)
{
    if (anti_alaised == d_antiAliased)
        return;

    d_antiAliased = anti_alaised;
    updateFont();
}
