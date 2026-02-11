writeAsDX()
{

  string fn=makeFilename();

  ofstream out_file(fn.c_str());
  out_file << "points = " << m_save_map.size() << endl;
  out_file << "format = ascii" << endl;
  out_file << "dependency = positions, positions" << endl;
  out_file << "interleaving = field" << endl;
  out_file << "field = locations, " << m_field_name << endl;
  out_file << "structure = 3-vector, scalar" << endl;
  out_file << "type = float, float  " << endl;
  out_file << "header =  marker \"Start\\n\"" << endl;
  out_file << endl << "end" << endl;
  out_file << "Start" << endl;


  for(map<int,double>::iterator iter=m_save_map.begin();
      iter!=m_save_map.end();
      iter++){
    out_file << m_pos_map[iter->first]  << " " << iter->second << endl;
  }
  out_file.close();
  m_save_map.erase(m_save_map.begin(),m_save_map.end());
  m_pos_map.erase(m_pos_map.begin(),m_pos_map.end());
  m_rad_map.erase(m_rad_map.begin(),m_rad_map.end());
}
