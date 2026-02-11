call(IComposer& r, IRemoteProcedure& method, IDecomposer** argv, unsigned argc)
{
    _method = &method;
    _state = OnBegin;

    prepareRequest(method.name(), argv, argc);

    std::istringstream is(execute());
    _ts.attach(is);
    _reader.reset(_ts);
    _deserializer.begin();
    _scanner.begin(_deserializer, r);

    while( _reader.get().type() !=  cxxtools::xml::Node::EndDocument )
    {
        const cxxtools::xml::Node& node = _reader.get();
        advance(node);
        _reader.next();
    }


    if (_method->failed() )
    {
        _method = 0;
        _state = OnBegin;
        throw _fault;
    }

    _method = 0;
    _state = OnBegin;


}
