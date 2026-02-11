native_handle()
    {
        detail::thread_data_ptr const local_thread_info=(get_thread_info)();
        if(local_thread_info)
        {
            lock_guard<mutex> lk(local_thread_info->data_mutex);
            return local_thread_info->thread_handle;
        }
        else
        {
            return pthread_t();
        }
    }
