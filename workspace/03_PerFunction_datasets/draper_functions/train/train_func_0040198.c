isValid()
{
    if (this->getDUID()->getLen()>2)
        return true;
    return false;
}
