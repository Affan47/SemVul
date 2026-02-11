getFieldType(FXint i){
  const FXchar * type=NULL;
  if (statement) {
    type = sqlite3_column_decltype((sqlite3_stmt*)statement,i);
    if (type==NULL)
      return TYPE_NULL;
    else if (comparecase("INTEGER",type)==0)
      return TYPE_INTEGER;
    else if (comparecase("FLOAT",type)==0)
      return TYPE_FLOAT;
    else if (comparecase("TEXT",type)==0)
      return TYPE_TEXT;
    else if (comparecase("BLOB",type)==0)
      return TYPE_BLOB;
    else
      return TYPE_NULL;
    }
  else {
    return TYPE_NULL;
    }
  }
