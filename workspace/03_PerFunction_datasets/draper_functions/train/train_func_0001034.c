cloud_on() const
{
    string value;
    if (file_.get_value("cloud", value))
    {
        return value == "on";
    }

    return true;
}
