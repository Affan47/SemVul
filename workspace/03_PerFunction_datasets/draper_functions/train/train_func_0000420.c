method_e(Interp &interp, const RefPtr<Expr> &arg, const RefPtr<Obj> &)
    {
      Val tmp_prev=interp.top_scope()->self();

      if(!tmp_prev.obj()->is_arg_name()) {
        return interp.nil_val();
      }
      Val tmp_rcvr=tmp_prev.obj()->rcvr();
      Method new_method;
      RefPtr<Obj> new_data;

      if(tmp_rcvr.obj()->rcvr().obj().get()!=0) {
        new_method=Method(tmp_prev.obj()->arg_name(), arg, true);
        do {
          new_data=interp.arg_obj()->clone();
          new_data->def_method("a", new_method);
          new_data->set_arg_name(tmp_rcvr.obj()->arg_name());
          new_method=Method(arg_a, new_data);
          tmp_prev=tmp_rcvr;
          tmp_rcvr=tmp_prev.obj()->rcvr();
        } while(tmp_rcvr.obj()->rcvr().obj().get()!=0);
      } else {
        new_method=Method(tmp_prev.obj()->arg_name(), arg);
      }
      Val new_rcvr(tmp_rcvr.i(), tmp_rcvr.obj()->clone());

      new_rcvr.obj()->def_method(tmp_prev.obj()->method_name(), new_method);
      return new_rcvr;
    }
