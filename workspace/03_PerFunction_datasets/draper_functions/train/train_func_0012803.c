li_append_variable(li_object *var, li_object *val,
        li_object *env) {
    if (!li_is_symbol(var))
        li_error("not a variable", var);
    if (env->data.env.size == env->data.env.cap) {
        env->data.env.cap *= 2;
        env->data.env.array = li_allocate(env->data.env.array,
                env->data.env.cap, sizeof(*env->data.env.array));
    }
    env->data.env.array[env->data.env.size].var = var;
    env->data.env.array[env->data.env.size].val = val;
    env->data.env.size++;
}
