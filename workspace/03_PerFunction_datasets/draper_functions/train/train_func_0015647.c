is_open() const
{
    return dev_length() != 0 && is_open0(FC_DEVICE);
}
