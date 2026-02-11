plus(pobject env, pobject params)
{
    float result = 0;
    while (is_cons(params)) {
        pobject o = eval(env, cons_car(params));
        if (is_number(o))
            result += number_value(o);
        params = cons_cdr(params);
    }

    return gc_add(number_new(result));
}
