Builtin(const UnitPtr& unit, Kind kind) :
    SyntaxTreeBase(unit),
    Type(unit),
    _kind(kind)
{


    _definitionContext = 0;
}
