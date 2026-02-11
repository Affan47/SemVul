prim_compareVersions(EvalState & state, Value * * args, Value & v)
{
    string version1 = state.forceStringNoCtx(*args[0]);
    string version2 = state.forceStringNoCtx(*args[1]);
    mkInt(v, compareVersions(version1, version2));
}
