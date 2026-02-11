default_set_domain (default_catalog_reader_ty *this, char *name)
{
  if (this->allow_domain_directives)

    this->domain = name;
  else
    {
      po_gram_error_at_line (&gram_pos,
                             _("this file may not contain domain directives"));


      free (name);
    }
}
