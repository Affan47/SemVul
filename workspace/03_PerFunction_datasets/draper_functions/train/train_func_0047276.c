generate_rule_params_simple_assignment(ste *enclosures)


{
  if ( enclosures != NULL &&
       ( enclosures->getvalue()->getclass() == decl::Quant ||
     enclosures->getvalue()->getclass() == decl::Alias ||
     enclosures->getvalue()->getclass() == decl::Choose ) )
    {
      generate_rule_params_simple_assignment(enclosures->getnext() );
      if (enclosures->getvalue()->gettype()->gettypeclass() == typedecl::Union)
    {
      if ( enclosures->getvalue()->getclass() == decl::Choose )
        fprintf(codefile,
            "    %s.unionassign( r %% %d );\n"
            "    r = r / %d;\n",
            enclosures->getvalue()->generate_code(),
            enclosures->getvalue()->gettype()->getsize(),
            enclosures->getvalue()->gettype()->getsize()
            );
      if ( enclosures->getvalue()->getclass() == decl::Quant )
        fprintf(codefile,
            "    %s.unionassign(r %% %d);\n"
            "    r = r / %d;\n",
            enclosures->getvalue()->generate_code(),
            enclosures->getvalue()->gettype()->getsize(),
            enclosures->getvalue()->gettype()->getsize()
            );
    }
      else
    {
      if ( enclosures->getvalue()->getclass() == decl::Choose )
        fprintf(codefile,
            "    %s.value((r %% %d) + %d);\n"
            "    r = r / %d;\n",
            enclosures->getvalue()->generate_code(),
            enclosures->getvalue()->gettype()->getsize(),
            enclosures->getvalue()->gettype()->getleft(),
            enclosures->getvalue()->gettype()->getsize()
            );
      if ( enclosures->getvalue()->getclass() == decl::Quant )
        fprintf(codefile,
            "    %s.value((r %% %d) + %d);\n"
            "    r = r / %d;\n",
            enclosures->getvalue()->generate_code(),
            enclosures->getvalue()->gettype()->getsize(),
            enclosures->getvalue()->gettype()->getleft(),
            enclosures->getvalue()->gettype()->getsize()
            );
    }
    }
}
