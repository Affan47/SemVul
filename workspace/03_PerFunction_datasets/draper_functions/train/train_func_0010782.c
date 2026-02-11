displayRoute(void)
{
    if (_display_route.empty())
    {

        _display_route = _route.simplify();
    }
    return _display_route;
}
