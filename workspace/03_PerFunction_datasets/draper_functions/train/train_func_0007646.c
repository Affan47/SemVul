run(Workqueue* workqueue, const Task* task)
{


  this->symtab_->detect_odr_violations(task, this->options_.output_file_name());

  Layout* layout = this->layout_;
  off_t file_size = layout->finalize(this->input_objects_,
				     this->symtab_,
				     this->target_,
				     task);


  if (this->mapfile_ != NULL)
    {
      this->mapfile_->print_discarded_sections(this->input_objects_);
      layout->print_to_mapfile(this->mapfile_);
    }

  Output_file* of;
  if (layout->incremental_base() == NULL)
    {
      of = new Output_file(parameters->options().output_file_name());
      if (this->options_.oformat_enum() != General_options::OBJECT_FORMAT_ELF)
	of->set_is_temporary();
      of->open(file_size);
    }
  else
    {
      of = layout->incremental_base()->output_file();


      if (parameters->incremental_update())
	layout->incremental_base()->apply_incremental_relocs(this->symtab_,
							     this->layout_,
							     of);

      of->resize(file_size);
    }


  gold::queue_final_tasks(this->options_, this->input_objects_,
			  this->symtab_, layout, workqueue, of);
}
