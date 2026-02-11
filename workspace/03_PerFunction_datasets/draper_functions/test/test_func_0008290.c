make_ready_at_thread_exit(shared_ptr<shared_state_base> as)
    {
      detail::thread_data_base* const current_thread_data(detail::get_current_thread_data());
      if(current_thread_data)
      {
        current_thread_data->make_ready_at_thread_exit(as);
      }
    }
