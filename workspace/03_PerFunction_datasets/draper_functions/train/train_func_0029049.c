set_special(string * spec_name, list<Parameter *> * params,
                       Parameter * init)
{
  type=1;
  if (spec_name)
    special_type=*spec_name;


  if (initvalue)
    delete initvalue;
  if (parameters)
    {
      list<Parameter *>::iterator pi;
      for (pi=parameters->begin();
           pi!=parameters->end();
           pi++)
        if (*pi)
          delete (*pi);
      delete parameters;
    }


  initvalue=init;
  parameters=params;
}
