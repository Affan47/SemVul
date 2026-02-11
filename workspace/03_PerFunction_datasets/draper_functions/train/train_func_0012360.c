xml_read_multi_voice_info (xmlNodePtr current_node, xmlDocPtr doc,
				       gregorio_score * score)
{

  int number_of_voices = 0;
  gregorio_voice_info *voice_info;
  gregorio_add_voice_info (&score->first_voice_info);
  voice_info = score->first_voice_info;
  while (current_node)
    {


      xml_read_voice_info (current_node->xmlChildrenNode, doc,
				       voice_info);
      gregorio_add_voice_info (&voice_info);
      number_of_voices++;
    }
  score->number_of_voices = number_of_voices;

}
