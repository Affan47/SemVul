k_mass ()
{
    int wa = wheels_area();
    float ma0 = 50.0;


    float km = wa > 0? ma0 / (ma0 + total_mass() / 8 / (float) wa) : 0;

    return km;
}
