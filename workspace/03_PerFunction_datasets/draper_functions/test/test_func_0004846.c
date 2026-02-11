cruise_thrust (int amount)
{
    if (!amount)
        return;
    int max_vel = (safe_velocity() * 11 / 10000 + 1) * 1000;
    cruise_velocity += amount;
    cruise_velocity = cruise_velocity / abs(amount) * abs(amount);
    if (cruise_velocity > max_vel)
        cruise_velocity = max_vel;
    else
    if (-cruise_velocity > max_vel / 4)
        cruise_velocity = -max_vel / 4;
}
