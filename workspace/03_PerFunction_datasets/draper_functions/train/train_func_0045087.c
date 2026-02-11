add_property(
    char const* name, object const& fget, char const* docstr)
  {
      object property(
          (python::detail::new_reference)
          PyObject_CallFunction((PyObject*)&PyProperty_Type, const_cast<char*>("Osss"), fget.ptr(), 0, 0, docstr));

      this->setattr(name, property);
  }
