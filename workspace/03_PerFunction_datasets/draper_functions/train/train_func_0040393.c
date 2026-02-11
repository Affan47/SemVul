UpdateWeather()
{
    Player* player = sWorld.FindPlayerInZone(m_zone);
    if (!player)
        return false;


    if (m_grade >= 1)
        m_grade = 0.9999f;
    else if (m_grade < 0)
        m_grade = 0.0001f;

    WeatherState state = GetWeatherState();

    WorldPacket data(SMSG_WEATHER, (4 + 4 + 1));
    data << uint32(state) << (float)m_grade << uint8(0);
    player->SendMessageToSet(&data, true);


    char const* wthstr;
    switch (state)
    {
        case WEATHER_STATE_LIGHT_RAIN:
            wthstr = "light rain";
            break;
        case WEATHER_STATE_MEDIUM_RAIN:
            wthstr = "medium rain";
            break;
        case WEATHER_STATE_HEAVY_RAIN:
            wthstr = "heavy rain";
            break;
        case WEATHER_STATE_LIGHT_SNOW:
            wthstr = "light snow";
            break;
        case WEATHER_STATE_MEDIUM_SNOW:
            wthstr = "medium snow";
            break;
        case WEATHER_STATE_HEAVY_SNOW:
            wthstr = "heavy snow";
            break;
        case WEATHER_STATE_LIGHT_SANDSTORM:
            wthstr = "light sandstorm";
            break;
        case WEATHER_STATE_MEDIUM_SANDSTORM:
            wthstr = "medium sandstorm";
            break;
        case WEATHER_STATE_HEAVY_SANDSTORM:
            wthstr = "heavy sandstorm";
            break;
        case WEATHER_STATE_THUNDERS:
            wthstr = "thunders";
            break;
        case WEATHER_STATE_BLACKRAIN:
            wthstr = "blackrain";
            break;
        case WEATHER_STATE_FINE:
        default:
            wthstr = "fine";
            break;
    }

    DETAIL_FILTER_LOG(LOG_FILTER_WEATHER, "Change the weather of zone %u to %s.", m_zone, wthstr);

    return true;
}
