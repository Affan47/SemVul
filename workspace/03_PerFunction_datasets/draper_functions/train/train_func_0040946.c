contactMap (::xercesc::InputSource& i,
              ::xml_schema::flags f,
              const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::BioXSD::FeatureRecord > r (
      ::freecontact_output_xsd::contactMap (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }
