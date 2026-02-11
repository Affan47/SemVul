FrequencyStep() const
{
    if (N > 0) return (omega_max - omega_min) / Real(N-1);
    return 0.0;
}
