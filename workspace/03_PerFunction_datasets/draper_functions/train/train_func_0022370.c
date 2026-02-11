eval(EvalState & state, Env & env, Value & v)
{
    Value v1; state.eval(env, e1, v1);
    state.forceList(v1);
    Value v2; state.eval(env, e2, v2);
    state.forceList(v2);
    state.mkList(v, v1.list.length + v2.list.length);
    for (unsigned int n = 0; n < v1.list.length; ++n)
        v.list.elems[n] = v1.list.elems[n];
    for (unsigned int n = 0; n < v2.list.length; ++n)
        v.list.elems[n + v1.list.length] = v2.list.elems[n];
}
