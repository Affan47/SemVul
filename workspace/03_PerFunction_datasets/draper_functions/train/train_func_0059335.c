new_book ()
{
  boost::shared_ptr<Ekiga::FormRequestSimple> request = boost::shared_ptr<Ekiga::FormRequestSimple> (new Ekiga::FormRequestSimple (boost::bind (&OPENLDAP::Source::on_new_book_form_submitted, this, _1, _2)));
  struct BookInfo bookinfo;

  bookinfo.name = "";
  bookinfo.uri = "ldap://localhost/dc=net?cn,telephoneNumber?sub?(cn=$)";
  bookinfo.authcID = "";
  bookinfo.password = "";
  bookinfo.saslMech = "";
  bookinfo.sasl = false;
  bookinfo.starttls = false;

  OPENLDAP::BookInfoParse (bookinfo);
  OPENLDAP::BookForm (request, bookinfo, _("Create LDAP directory"));

  questions (request);
}
