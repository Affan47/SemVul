init()
{
  if(!gtype_)
  {

    class_init_func_ = &Hyperlink_Class::class_init_function;


    register_derived_type(atk_hyperlink_get_type());


  Action::add_interface(get_type());

  }

  return *this;
}
