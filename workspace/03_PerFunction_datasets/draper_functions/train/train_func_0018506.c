extractFieldInfo(istrstream& strm,
                            char* field_name_buffer,
                            char** var_name_buffers,
                            char& data_type,
                            short& dim1, short& dim2,
                            short& nof_variables,
                            bool& is_inactive)
{
  is_inactive = false;


  if ( strm.peek() ==  '-' ) {
    extractInactiveMarker(strm);
    is_inactive = true;
  }


  if ( strm.peek() ==  '(' ) {
    extractFieldSizeAndVars(strm, var_name_buffers, dim1, dim2, nof_variables);
  }

  extractFieldNameAndType(strm, field_name_buffer, data_type);


  if ( strm.peek() ==  '(' ) {
    extractFieldSizeAndVars(strm, var_name_buffers, dim1, dim2, nof_variables);
  }
}
