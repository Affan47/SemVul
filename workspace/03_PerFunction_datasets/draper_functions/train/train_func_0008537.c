visitModuleEnd(const ModulePtr& p)
{
    assert(!_moduleStack.empty());
    _out << sp << nl << "# End of module " << _moduleStack.front();
    _moduleStack.pop_front();

    if(!_moduleStack.empty())
    {
        _out << sp << nl << "__name__ = '" << _moduleStack.front() << "'";
    }
}
