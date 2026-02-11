deleteThis()
{
    if (_next) {
        _str = _next->_str;
        _type = _next->_type;
        _isUnsigned = _next->_isUnsigned;
        _isSigned = _next->_isSigned;
        _isPointerCompare = _next->_isPointerCompare;
        _isLong = _next->_isLong;
        _isUnused = _next->_isUnused;
        _isStandardType = _next->_isStandardType;
        _isExpandedMacro = _next->_isExpandedMacro;
        _varId = _next->_varId;
        _fileIndex = _next->_fileIndex;
        _linenr = _next->_linenr;
        _link = _next->_link;
        _scope = _next->_scope;
        _function = _next->_function;
        _variable = _next->_variable;
        if (_link)
            _link->link(this);

        deleteNext();
    } else if (_previous && _previous->_previous) {
        _str = _previous->_str;
        _type = _previous->_type;
        _isUnsigned = _previous->_isUnsigned;
        _isSigned = _previous->_isSigned;
        _isPointerCompare = _previous->_isPointerCompare;
        _isLong = _previous->_isLong;
        _isUnused = _previous->_isUnused;
        _isStandardType = _previous->_isStandardType;
        _isExpandedMacro = _previous->_isExpandedMacro;
        _varId = _previous->_varId;
        _fileIndex = _previous->_fileIndex;
        _linenr = _previous->_linenr;
        _link = _previous->_link;
        _scope = _previous->_scope;
        _function = _previous->_function;
        _variable = _previous->_variable;
        if (_link)
            _link->link(this);

        Token* toDelete = _previous;
        _previous = _previous->_previous;
        _previous->_next = this;

        delete toDelete;
    } else {


        str("");
    }
}
