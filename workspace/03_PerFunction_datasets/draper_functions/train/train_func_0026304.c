value(const Expression_eval_info* eei)
{

  if (parameters->options().user_set_Ttext()
      && this->segment_name_ == ".text")
    return parameters->options().Ttext();
  else if (parameters->options().user_set_Tdata()
	   && this->segment_name_ == ".data")
    return parameters->options().Tdata();
  else if (parameters->options().user_set_Tbss()
	   && this->segment_name_ == ".bss")
    return parameters->options().Tbss();
  else
    {
      uint64_t ret = this->arg_value(eei, NULL);

      if (eei->result_section_pointer != NULL)
        *eei->result_section_pointer = NULL;
      return ret;
    }
}
