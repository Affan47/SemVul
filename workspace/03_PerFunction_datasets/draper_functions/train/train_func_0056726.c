li_environment_lookup(li_object *env, li_object *var) {
    int i;

    while (env) {
        for (i = 0; i < env->data.env.size; i++)
            if (env->data.env.array[i].var == var)
                return env->data.env.array[i].val;
        env = env->data.env.base;
    }
    li_error("unbound variable", var);
    return li_null;
}
