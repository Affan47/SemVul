change_luck(schar n)
{
    u.uluck += n;
    if (u.uluck < 0 && u.uluck < LUCKMIN)
    {
        u.uluck = LUCKMIN;
    }
    if (u.uluck > 0 && u.uluck > LUCKMAX)
    {
        u.uluck = LUCKMAX;
    }
}
