send_method(const string &name, Interp &interp, const RefPtr<Expr> &arg, const Ptr<Tail> &tail) const
  {
    if(m_obj->is_method(name)) {
      Method tmp_method=m_obj->method(name);
      Val tmp_r=tmp_method.call(interp, *this, arg, tail);

      interp.set_last_method(tmp_method);
      return tmp_r;
    } else {
      interp.set_last_method(Method());
      return interp.nil_val();
    }
  }
