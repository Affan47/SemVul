fileio_puts(const fn_call& fn)
{

    string str = fn.arg(0).to_string();
    return as_value(::puts(str.c_str()));
}
