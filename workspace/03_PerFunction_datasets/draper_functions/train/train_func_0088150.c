make_reduce(char*label, vvp_net_fun_t*red, struct symb_s arg)
{
      vvp_net_t*ptr = new vvp_net_t;
      ptr->fun = red;

      define_functor_symbol(label, ptr);
      free(label);

      input_connect(ptr, 0, arg.text);
}
