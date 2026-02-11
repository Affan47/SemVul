output_sif(ostream& out, short indent_size, short indent_level)
{


  if ( NO_INDEX == getEquationId() ) {
    return out;
  }

  char* QM = "\"";
  short is = indent_size;
  short il = indent_level;

  int nof_parameter_ids = 4;
  const char* names[4] = { SIF_BODY_FORCE, SIF_EQUATION, SIF_INITIAL_CONDITION, SIF_MATERIAL};
  int ids[4] = { getBodyForceId(), getEquationId(), getInitialConditionId(), getMaterialId()};


  LibFront::output_scalar(out, is, il, SIF_BODY, NULL, tag);


  if ( model->getSolverKeywordTypeGiven(SIF_BODY, "Name") ) {
    LibFront::output_scalar(out, is, il + 1, "Name =", NULL, name, true);
  } else {
    LibFront::output_scalar(out, is, il + 1, "Name = String", NULL, name, true);
  }
  out << endl;


  if ( bodyParameterId != NO_INDEX ) {
    Parameter* p = model->getParameterById(ECIF_BODY_PARAMETER, bodyParameterId);

    if ( p != NULL ) {

      SifOutputControl soc;
      soc.outputId = false;
      soc.outputName = false;
      soc.outputType = false;
      soc.outputAll = false;
      soc.sectionName = SIF_BODY;

      p->output_sif(out, indent_size, indent_level, soc);
    }
  }


  for (short i = 0; i < nof_parameter_ids; i++) {

    strstream strm;


    if ( 0 == strcmp(SIF_EQUATION, names[i]) || ids[i] != NO_INDEX ) {

      strm << names[i] << " =";
      if ( !model->getSolverKeywordTypeGiven(SIF_BODY, names[i]) ) {
        strm << " Integer" << ends;
      }
      strm << ends;
      LibFront::output_scalar(out, is, 1 + il, strm.str(), NULL, ids[i]);
    }
  }

  return out;
}
