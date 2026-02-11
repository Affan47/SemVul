cf_tai64n_now(value unit)
{
    CAMLparam0();
    CAMLlocal1(result);

    Cf_tai64n_t x;

    cf_tai64n_update(&x);
    result = cf_tai64n_alloc(&x);

    CAMLreturn(result);
}
