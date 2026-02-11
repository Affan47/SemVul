output_sif(ostream& out, short indent_size, short indent_level,
                           const char* section_name, bool output_equal_sign)
{

  if ( nofDataStrings == 0 ||
       !fieldInfo->outputSif
     )
    return out;


  if ( !fieldInfo->isArray &&
       nofDataStrings == 1 &&
       !fieldInfo->alwaysOutput &&
       LibFront::ncEqual("Logical", (char*)fieldInfo->valueType) &&
       LibFront::ncEqual("False", dataStrings[0])
     )
    return out;


  if ( !fieldInfo->isArray &&
       nofDataStrings == 1 &&
       !fieldInfo->alwaysOutput &&
       LibFront::ncEqual("String", (char*)fieldInfo->valueType) &&
       LibFront::ncEqual("None", dataStrings[0])
     )
    return out;

  short is = indent_size;
  short il = indent_level;

  bool type_printed = false;

  LibFront::indent(out, is, il);


  output_sif_name(out, false);


  if (fieldInfo->isArray) {
    output_sif_size(out);
  }


  if ( output_equal_sign &&
       !LibFront::ncEqual("Include", fieldInfo->sifName)
     ) {
    out << " = ";
  } else {
    out << " ";
  }


  if (nofVariables > 0) {
    output_sif_variableNames(out);
  }


  if ( !model->getSolverKeywordTypeGiven(section_name, getSifName()) &&
       fieldInfo->outputSifType
     ) {


    if ( nofVariables > 0 || fieldInfo->isProcName ) {
      out << endl;
      LibFront::indent(out, is, ++il);
    }

    output_sif_type(out);
    type_printed = true;
  }


  output_sif_data(out, is, ++il, type_printed, true);

  return out;
}
