dump(std::ostream& out, const std::string& praefix) const
{
    if (!_name.empty())
        out << praefix << "name = \"" << _name << "\"\n";

    if (_t != t_none)
    {
        out << praefix << "type = " << (_t == t_none ? "none" :
                                        _t == t_string ? "string" :
                                        _t == t_string8 ? "string8" :
                                        _t == t_char ? "char" :
                                        _t == t_bool ? "bool" :
                                        _t == t_int ? "int" :
                                        _t == t_uint ? "uint" :
                                        _t == t_float ? "float" : "?") << '\n';

        out << praefix << "value = ";

        switch (_t)
        {
            case t_none:    out << '-'; break;
            case t_string:  out << '"' << _String().narrow() << '"'; break;
            case t_string8: out << '"' << _String8() << '"'; break;
            case t_char:    out << '\'' << _u._c << '\''; break;
            case t_bool:    out << _u._b; break;
            case t_int:     out << _u._i; break;
            case t_uint:    out << _u._u; break;
            case t_float:   out << _u._f; break;
        }

        out << '\n';
    }

    if (!_type.empty())
        out << praefix << "typeName = " << _type << '\n';
    if (!_nodes.empty())
    {
        std::string p = praefix + '\t';
        for (std::vector<SerializationInfo>::size_type n = 0; n < _nodes.size(); ++n)
        {
            out << praefix << "node[" << n << "]\n";
            _nodes[n].dump(out, p);
        }
    }
}
