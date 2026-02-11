ToString() const
{
    std::stringstream str;
    const char * mode_str[ModesEnd] = {"Linear", "CatmullRom", "Bezier3", "Uninitialized"};

    index_type count = this->points.size();
    str << "mode: " << mode_str[mode()] << std::endl;
    str << "points count: " << count << std::endl;
    for (index_type i = 0; i < count; ++i)
        str << "point " << i << " : " << points[i].toString() << std::endl;

    return str.str();
}
