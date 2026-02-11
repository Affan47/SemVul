extractInt( KJS::ExecState *exec, const KJS::List &args, int idx, int defaultValue )
{
    if( args.size() > idx )
    {
        return extractInt( exec, args[idx] );
    }
    return defaultValue;
}
