DataComparator(const Glib::RefPtr<DataModel>& old_model, const Glib::RefPtr<DataModel>& new_model)
:

  Glib::ObjectBase(0),
  Glib::Object(Glib::ConstructParams(datacomparator_class_.init(), "old_model", Glib::unwrap(old_model), "new_model", Glib::unwrap(new_model), static_cast<char*>(0)))
{


}
