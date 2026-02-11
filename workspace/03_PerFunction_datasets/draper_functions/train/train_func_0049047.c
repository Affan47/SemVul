clean_up_after_relaxation()
{

  Script_sections* script_section = this->script_options_->script_sections();
  script_section->release_segments();
  this->restore_segments(this->segment_states_);


  for (Section_list::iterator p = this->section_list_.begin();
       p != this->section_list_.end();
       ++p)
    {
      (*p)->restore_states();


      if ((*p)->section_offsets_need_adjustment())
	(*p)->adjust_section_offsets();

      (*p)->reset_address_and_file_offset();
    }


  for (Data_list::iterator p = this->special_output_list_.begin();
       p != this->special_output_list_.end();
       ++p)
    (*p)->reset_address_and_file_offset();


  for (Output_section_data_list::const_iterator p =
	 this->script_output_section_data_list_.begin();
       p != this->script_output_section_data_list_.end();
       ++p)
    delete *p;
  this->script_output_section_data_list_.clear();


  this->reset_relax_output();
}
