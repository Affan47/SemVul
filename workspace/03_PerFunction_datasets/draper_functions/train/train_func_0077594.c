li_environment_assign(li_object *env, li_object *var,
        li_object *val)
{
    int i;

    while (env) {
        for (i = 0; i < env->data.env.size; i++)
            if (env->data.env.array[i].var == var) {
                env->data.env.array[i].val = val;
                return 1;
            }
        env = env->data.env.base;
    }
    return 0;
}
