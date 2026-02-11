write_to_GMConf()
{
	m_pVariablesMap->transfer_widgets_to_variables();
	GMConf["usebook"] = m_usebook? "1":"0";
	GMConf["desktop_size"] = m_size_big?"1":"0";
	GMConf["engine_depth"] = m_depth;
	GMConf["step_time"] = m_step_time;
	GMConf["play_time"] = m_play_time;
	GMConf["engine_name"] = m_engine_name;
	GMConf["line_color"] = m_line_color;

	if(cbtheme->get_active_text() == "wood")
		GMConf["themes"] = "wood";
	else
		GMConf["themes"] = "west";

}
