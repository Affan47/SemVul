GetPassenger(uint8 seat) const
{
    for (PassengerMap::const_iterator itr = m_passengers.begin(); itr != m_passengers.end(); ++itr)
        if (itr->second->GetTransportSeat() == seat)
            return (Unit*)itr->first;

    return NULL;
}
