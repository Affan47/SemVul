write( Node& out ) const
{
    const int boxheight[4] = { 2000, 1000, 1000, 1250 };
    const char* paths[4] = {
        "M0 2000 L750 0 1500 2000 1250 2000 750 500 250 2000Z",
        "M0 1000 L750 0 1500 1000Z",
        "M0 1000 L750 0 1500 1000 750 750Z",
        "M0 1000 L750 0 1500 1000 750 1250Z"
    };
    Node& arrow = out.subnode("draw:marker");
    arrow["draw:name"] << name();


    arrow["svg:viewBox"] << "0 0 1500 " << boxheight[arrow_type];
    arrow["svg:d"] << paths[ arrow_type ];

    return out;
}
