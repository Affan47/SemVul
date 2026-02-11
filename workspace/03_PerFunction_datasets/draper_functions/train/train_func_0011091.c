get_name () const
{
  std::string name;

  name = (const gchar *)e_contact_get_const (econtact,
					     E_CONTACT_FULL_NAME);

  return name;
}
