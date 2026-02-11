send (Message_ptr m)
  {
    if (Data const* data = static_cast<Data const*> (m->find (Data::id)))
    {
      size_t max_payload_size (
        params_.max_packet_size () - max_service_size);

      if (max_payload_size > data->size ())
      {
        u32 max_size (max_payload_size - data->size ());
        u32 max_elem (NRTM::max_count (max_size));

        if (max_elem > 0)
        {
          Lock l (mutex_);

          Profile_ptr nrtm (create_nrtm (max_elem));

          if (nrtm.get ())
            m->add (nrtm);
        }
      }

      nrtm_timer_ = params_.nrtm_timeout ();
    }

    out_->send (m);
  }
