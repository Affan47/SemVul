propfindProp(const std::string &path, int depth,
                           const ne_propname *props,
                           const PropfindPropCallback_t &callback,
                           const Timespec &deadline)
{
    propfindURI(path, depth, props,
                boost::bind(&Session::propsIterate, _1, _2, boost::cref(callback)),
                deadline);
}
