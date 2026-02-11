createDataMember(const string& name, const TypePtr& type)
{
    checkPrefix(name);

    if(_unit->profile() == IceE)
    {
        if(!isLocal())
        {
            BuiltinPtr builtin = BuiltinPtr::dynamicCast(type);
            if((builtin && builtin->kind() == Builtin::KindObject))
            {
                string msg = "Struct data member `" + name + "' cannot be a value object.";
                _unit->error(msg);
                return 0;
            }
            ClassDeclPtr classDecl = ClassDeclPtr::dynamicCast(type);
            if(classDecl != 0 && !classDecl->isLocal())
            {
                string msg = "Struct data member `" + name + "' cannot be a value object.";
                _unit->error(msg);
                return 0;
            }
        }
    }

    ContainedList matches = _unit->findContents(thisScope() + name);
    if(!matches.empty())
    {
        DataMemberPtr p = DataMemberPtr::dynamicCast(matches.front());
        if(p)
        {
            if(_unit->ignRedefs())
            {
                p->updateIncludeLevel();
                return p;
            }
        }
        if(!_unit->caseSensitive() && matches.front()->name() != name)
        {
            string msg = "member `" + name + "' differs only in capitalization from ";
            msg += "member `" + matches.front()->name() + "'";
            _unit->error(msg);
        }
        else
        {
            string msg = "redefinition of struct member `" + name + "'";
            _unit->error(msg);
            return 0;
        }
    }


    if(name == this->name())
    {
        string msg = "struct name `";
        msg += name;
        msg += "' cannot be used as member name";
        _unit->error(msg);
        return 0;
    }
    if(!_unit->caseSensitive())
    {
        string newName = name;
        toLower(newName);
        string thisName = this->name();
        toLower(thisName);
        if(newName == thisName)
        {
            string msg = "struct member `" + name + "' differs only in capitalization from enclosing struct name `";
            msg += this->name() + "'";
            _unit->error(msg);
        }
    }


    if(type.get() == this)
    {
        string msg = "struct `";
        msg += this->name();
        msg += "' cannot contain itself";
        _unit->error(msg);
        return 0;
    }


    if(!isLocal() && type->isLocal())
    {
        string msg = "non-local " + kindOf() + "`" + this->name() + "' cannot contain local member `" + name + "'";
        _unit->error(msg);
    }

    DataMemberPtr p = new DataMember(this, name, type);
    _contents.push_back(p);
    return p;
}
