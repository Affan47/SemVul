makeFilename()
{
  ostringstream fn;
  string suffix;

  switch (m_write_type){
  case WRITE_TYPE_DX : suffix=".dx"; break;
  case WRITE_TYPE_POV : suffix=".pov"; break;
  case WRITE_TYPE_SILO : suffix=".silo"; break;
  case WRITE_TYPE_RAW2 : suffix=".dat"; break;
  case WRITE_TYPE_RAW : suffix=".dat"; break;
  case WRITE_TYPE_RAW_WITH_ID : suffix=".dat"; break;
  case WRITE_TYPE_RAW_WITH_POS_ID : suffix=".dat"; break;
  default : cerr << "AFieldMaster: wrong m_write_type in makeFilename" << endl;
  }
  fn << m_file_name << "." << m_save_count << suffix;
  m_save_count++;

  return fn.str();
}
