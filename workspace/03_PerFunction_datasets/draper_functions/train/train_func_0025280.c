createResponder(const Request& request)
{
    if (responders.empty())
    {
        return newResponder();
    }
    else
    {
        Responder* ret = responders.back();
        responders.pop_back();
        return ret;
    }
}
