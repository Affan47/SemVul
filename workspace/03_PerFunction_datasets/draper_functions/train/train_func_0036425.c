create_connection()
      {

        basic_connection* con = new basic_connection();

         {


          con->signal = static_cast<void*>(this);
          con->signal_data = 0;
          con->blocked_ = false ;
          con->signal_disconnect = &bound_object_destructed;
        }


        data->watch_bound_objects.reset(con);


        scoped_connection safe_connection(data->watch_bound_objects);


        for(std::vector<const trackable*>::iterator i =
              data->bound_objects.begin();
            i != data->bound_objects.end(); ++i) {

          BOOST_SIGNALS_NAMESPACE::detail::bound_object binding;
          (*i)->signal_connected(data->watch_bound_objects, binding);


          BOOST_SIGNALS_NAMESPACE::detail::auto_disconnect_bound_object
            disconnector(binding);


          con->bound_objects.push_back(binding);


          disconnector.release();
        }


        safe_connection.release();

        data->watch_bound_objects.set_controlling(true);
      }
