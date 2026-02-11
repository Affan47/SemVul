run(Workqueue*)
{

  Incremental_inputs* incremental_inputs = this->layout_->incremental_inputs();
  if (incremental_inputs != NULL)
    incremental_inputs->report_archive_begin(this->lib_, 0, NULL);

  this->lib_->add_symbols(this->symtab_, this->layout_, this->input_objects_);

  if (incremental_inputs != NULL)
    incremental_inputs->report_archive_end(this->lib_);
}
