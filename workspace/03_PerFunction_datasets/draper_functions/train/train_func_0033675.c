init()
{
  if(!gtype_)
  {

    class_init_func_ = &Selector_Class::class_init_function;


    register_derived_type(gx_selector_get_type());


  }

  return *this;
}
