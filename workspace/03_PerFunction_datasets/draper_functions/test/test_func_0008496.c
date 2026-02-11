HandleAuraModIncreaseHealth(bool apply, bool Real)
{
    Unit* target = GetTarget();

    switch (GetId())
    {


        case 54443:
        case 55233:
        case 61254:
            if (Real && apply)
                m_modifier.m_amount = target->GetMaxHealth() * m_modifier.m_amount / 100;


        case 12976:
        case 28726:
        case 31616:
        case 34511:
        case 44055: case 55915: case 55917: case 67596:
        case 50322:
        case 53479:
        case 59465:
        {
            if (Real)
            {
                if (apply)
                {
                    target->HandleStatModifier(UNIT_MOD_HEALTH, TOTAL_VALUE, float(m_modifier.m_amount), apply);
                    target->ModifyHealth(m_modifier.m_amount);
                }
                else
                {
                    if (int32(target->GetHealth()) > m_modifier.m_amount)
                        target->ModifyHealth(-m_modifier.m_amount);
                    else
                        target->SetHealth(1);
                    target->HandleStatModifier(UNIT_MOD_HEALTH, TOTAL_VALUE, float(m_modifier.m_amount), apply);
                }
            }
            return;
        }

        default:
            target->HandleStatModifier(UNIT_MOD_HEALTH, TOTAL_VALUE, float(m_modifier.m_amount), apply);
    }
}
